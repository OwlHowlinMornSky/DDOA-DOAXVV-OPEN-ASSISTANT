
namespace Helper {
	public class Worker {

		private Action<string[]> Log = (x) => {};
		private bool m_callbackForLogSetted = false;
		private Task? m_prevTask;
		private CancellationTokenSource? m_ctSrc;

		internal Worker() {
		}

		public void SetCallbackForLog(Action<string[]> action) {
			if (m_callbackForLogSetted)
				return;
			m_callbackForLogSetted = true;
			Log = action;
		}

		public bool IsRunning() {
			return m_prevTask != null && !m_prevTask.IsCompleted;
		}

		public void CancelWork() {
			if (m_ctSrc == null)
				return;
			m_ctSrc.Cancel();
		}

		public void StartWork(List<Step.Type> steps) {
			if (IsRunning()) {
				throw new WorkNotCompletedException();
			}
			m_ctSrc = new();
			m_prevTask = Task.Run(() => { Work(steps, m_ctSrc.Token); }, m_ctSrc.Token);
			return;
		}

		private void Work(List<Step.Type> steps, CancellationToken ct) {
			Global.WndHandler.SetCancellationToken(ct);

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

	}
}
