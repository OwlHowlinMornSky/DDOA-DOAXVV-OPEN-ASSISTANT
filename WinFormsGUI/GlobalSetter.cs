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
			Program.helper.SetChallengeForNewOrLast(Settings.Core.Default.PlayNewMatch);
			Program.helper.SetMouseSendInputOrSendMessage(Settings.Core.Default.CtrlSendInput);
			Program.helper.SetShowCaptureOrNot(Settings.Core.Default.ShowCapture);
			Program.helper.SetKeepAwakeOrNot(Settings.Core.Default.KeepAwake);
			Program.helper.SetKeepScreenOnOrNot(Settings.Core.Default.KeepScreenOn);
			switch (Settings.Core.Default.AwardMatch) {
			case 0:
				Program.helper.SetChallengeCheckAwardOrNot(false);
				Program.helper.SetChallengePlayAwardOrNot(true);
				break;
			case 1:
				Program.helper.SetChallengeCheckAwardOrNot(true);
				Program.helper.SetChallengePlayAwardOrNot(true);
				break;
			case 2:
				Program.helper.SetChallengeCheckAwardOrNot(true);
				Program.helper.SetChallengePlayAwardOrNot(false);
				break;
			default:
				Program.helper.SetChallengeCheckAwardOrNot(false);
				Program.helper.SetChallengePlayAwardOrNot(false);
				break;
			}

			Program.helper.SetUseCamFP(Settings.Core.Default.AutoUseCamFp);

			Program.helper.SetDoDailyCheck(Settings.Core.Default.DoDailyCheck);
			Program.helper.SetDoDailyShot(Settings.Core.Default.DoDailyShot);

			Program.helper.SetUseHook(Settings.Core.Default.UseHook);

			Program.helper.SetChaAskForManual(Settings.Core.Default.ChaPauseAndAskForManual);

			Program.helper.SetChaAutoUseDrink(Settings.Core.Default.AutoUseDrink);
		}

		internal static void SaveSettings() {
			Settings.GUI.Default.Save();
			Settings.Core.Default.Save();
			//Settings.Param.Default.Save();
		}

		internal static Action<bool> OnSettedWndCloseBtnDisabled = x=>{};
		internal static void SetWndCloseBtnDisabled(bool value) {
			Settings.GUI.Default.DisableClose = value;
			OnSettedWndCloseBtnDisabled?.Invoke(value);
		}


	}
}
