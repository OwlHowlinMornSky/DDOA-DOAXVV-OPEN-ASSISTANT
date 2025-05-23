﻿/*
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

namespace Helper.Step {
	internal class Debug : IStep {
		public void Run(CancellationToken ct) {
			IStep.Log(
				GUICallbacks.LogInfo.Type.Notice,
				LogStr.StepDebugBegin
				);


			IStep.Log(
				GUICallbacks.LogInfo.Type.Notice,
				LogStr.ManualChaPageNavigate
				);

			Worker.PauseForManual(ct);

			IStep.TaskSleep(TimeSpan.FromSeconds(12), ct);

			IStep.Log(
				GUICallbacks.LogInfo.Type.Notice,
				LogStr.StepDebugEnd
				);
		}

		~Debug() {
			Dispose(false);
		}

		public void Dispose() {
			Dispose(true);
			GC.SuppressFinalize(this);
		}

		private bool _disposed = false;
		protected void Dispose(bool disposing) {
			if (_disposed)
				return;
			_disposed = true;
		}
	}
}
