
namespace Helper {
	public class WorkNotCompletedException : Exception {
	}
	public class NoSuchStepException : Exception {
	}

	public class TemplateListFormatException : Exception {
	}

	public class WndHandlerNotRunningException : Exception {
	}
	public class WndHandlerWndNotFoundException : Exception {
	}
	public class WndHandlerCaptureFailedException : Exception {
	}
	public class WndHandlerHookFailedException(string str) : Exception(str) {
	}

	public class StepCompleteException : Exception {
	}
	public class StepErrorContinueException(string str) : Exception(str) {
	}
	public class StepErrorCriticalException(string str) : Exception(str) {
	}
}
