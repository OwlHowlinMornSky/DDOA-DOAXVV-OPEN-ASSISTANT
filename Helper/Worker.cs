/*
*    DDOA-DOAXVV-OPEN-ASSISTANT
* 
*     Copyright 2023-2025  Tyler Parret True
* 
*    Licensed under the Apache License, Version 2.0 (the "License");
*    you may not use this file except in compliance with the License.
*    You may obtain a copy of the License at
* 
*        http://www.apache.org/licenses/LICENSE-2.0
* 
*    Unless required by applicable law or agreed to in writing, software
*    distributed under the License is distributed on an "AS IS" BASIS,
*    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*    See the License for the specific language governing permissions and
*    limitations under the License.
* 
* @Authors
*    Tyler Parret True <mysteryworldgod@outlook.com><https://github.com/OwlHowlinMornSky>
*/

namespace Helper {
	public static class Worker {

		private class TaskLock() {
			public bool isRunning = false;
			public CancellationTokenSource? ctSrc = null;
		}
		private static readonly TaskLock m_taskLock = new();

		private static AutoResetEvent m_resume = new(false);

		public static bool IsRunning() {
			lock (m_taskLock) {
				return m_taskLock.isRunning;
			}
		}

		public static void TryCancelWork() {
			lock (m_taskLock) {
				m_taskLock.ctSrc?.Cancel();
			}
		}

		public static void Resume() {
			m_resume.Set();
		}

		public static async void StartWork(IEnumerable<Step.Type> steps) {
			if (IsRunning())
				throw new WorkNotCompletedException();
			CancellationToken token;
			lock (m_taskLock) {
				m_taskLock.isRunning = true;
				m_taskLock.ctSrc = new();
				token = m_taskLock.ctSrc.Token;
			}
			await Task.Run(() => { Work(steps, token); }, token);
			lock (m_taskLock) {
				m_taskLock.ctSrc = null;
				m_taskLock.isRunning = false;
			}
			return;
		}

		private static void Work(IEnumerable<Step.Type> steps, CancellationToken ct) {
			WndHandler.SetCancellationToken(ct);

			GUICallbacks.LockTask(true);

			foreach (var steptype in steps) {
				ct.ThrowIfCancellationRequested();

				Step.IStep step;

				try {
					step = Step.IStep.CreateStep(steptype);
				}
				catch (NoSuchStepException ex) {
					GUICallbacks.Log(new(
						GUICallbacks.LogInfo.Type.Error,
						ex.Message
						));
					continue;
				}

				try {
					step.Run(ct);
				}
				catch (OperationCanceledException) {
					WndHandler.Reset();
					GUICallbacks.Log(new(
						GUICallbacks.LogInfo.Type.Info,
						LogStr.TaskCancelled
						));
					GUICallbacks.LockTask(false);
					return;
				}
				catch (Exception ex) {
					GUICallbacks.Log(new(
						GUICallbacks.LogInfo.Type.Error,
						LogStr.TaskErrInternalException,
						ex.Message + ": " + ex.StackTrace
						));
					break;
				}
			}
			WndHandler.Reset();

			GUICallbacks.Log(new(
				GUICallbacks.LogInfo.Type.Info,
				LogStr.TaskComplete
				));
			GUICallbacks.LockTask(false);
		}

		internal static void PauseForManual() {
			GUICallbacks.Pause();
			m_resume.WaitOne();
		}
	}
}
