using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Helper {
	public static class GUICallbacks {
		public struct LogInfo(LogInfo.Type type, string title, string? desc = null) {
			public enum Type {
				Info,
				Warn,
				Error
			}
			public Type type = type;
			public string title = title;
			public string? description = desc;
		}
		public static Action<LogInfo> Log { set; internal get; } = (x) => { };

		public static Action<bool> LockTask { set; internal get; } = (x) => { };
		public static Action<bool, Step.Type> LockSettings { set; internal get; } = (x, y) => { };
	}
}
