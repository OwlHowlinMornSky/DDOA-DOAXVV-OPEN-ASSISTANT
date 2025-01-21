using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WinFormsGUI {
	internal static class GlobalSetter {

		internal static void InitSettings() {
#if DEBUG
			Settings.Core.Default.ShowCapture = true;
#else
			Settings.Core.Default.ShowCapture = false;
#endif
		}

		internal static void SaveSettings() {
			Settings.GUI.Default.Save();
			Settings.Core.Default.Save();
		}

		internal static Action<bool> OnSettedWndCloseBtnDisabled = (x) => {};
		internal static void SetWndCloseBtnDisabled(bool value) {
			Settings.GUI.Default.DisableClose = value;
			OnSettedWndCloseBtnDisabled(value);
		}

	}
}
