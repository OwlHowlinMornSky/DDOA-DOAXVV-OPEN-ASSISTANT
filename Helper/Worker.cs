
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
					Log([$"{ex.Message}"]);
					throw;
					//continue;
				}
				catch (Exception ex) {
					ex.GetType().ToString();
					throw;
					continue;
				}

				try {
					step.Run(ct);
				}
				catch (WorkCannotContinueException ex) {
					// LOG
					throw;
					break;
				}
				catch (Exception ex) {
					throw;
					// LOG
				}
			}
		}

		internal static void PauseForManual() {
			m_resume.WaitOne();
		}
	}
}
