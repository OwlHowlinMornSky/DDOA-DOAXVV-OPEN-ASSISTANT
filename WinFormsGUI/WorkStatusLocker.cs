using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WinFormsGUI {
	internal static class WorkStatusLocker {

		/// <summary>
		/// 任务状态改变时锁定与解锁GUI的事件。
		/// </summary>
		internal static Action<bool> lockAction = x => { };

		private static bool isLocked = false;
		internal static bool Locked {
			get {
				return isLocked;
			}
		}

		internal static void WorkLock() {
			isLocked = true;
			lockAction?.Invoke(true);
		}

		internal static void WorkUnlock() {
			isLocked = false;
			lockAction?.Invoke(false);
		}

	}
}
