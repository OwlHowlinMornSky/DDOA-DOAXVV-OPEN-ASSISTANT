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

namespace WinFormsGUI {
	internal static class GlobalSetter {

		internal static TaskStatusRegistration Regist { get; } = new();

		internal static void InitSettings() {
#if DEBUG
			Settings.Core.Default.ShowCapture = true;
#else
			Settings.Core.Default.ShowCapture = false;
#endif
		}

		internal static void ApplySettings() {
			Helper.Settings.global.KeepAwake = Settings.Core.Default.KeepAwake;
			Helper.Settings.global.KeepScreenOn = Settings.Core.Default.KeepScreenOn;

			Helper.Settings.wndHandler.UseSendInput = Settings.Core.Default.CtrlSendInput;
			Helper.Settings.wndHandler.UseHook = Settings.Core.Default.UseHook;
			Helper.Settings.wndHandler.Debug_ShowCapture = Settings.Core.Default.ShowCapture;
			//Helper.Settings.wndHandler.Debug_DebugHandler = Settings.Core.Default;

			Helper.Settings.challenge.PlayMatch = Settings.Core.Default.PlayMatchType;
			Helper.Settings.challenge.SelectedActivityLevel = Settings.Core.Default.PlayLevel;
			Helper.Settings.challenge.SelectedActivityMatch = Settings.Core.Default.PlayLevelR;
			Helper.Settings.challenge.EnterAddition = Settings.Core.Default.AwardMatch == 1;
			Helper.Settings.challenge.CheckAddition = Settings.Core.Default.AwardMatch != 0;
			Helper.Settings.challenge.AutoUseCamFP = Settings.Core.Default.AutoUseCamFp;
			Helper.Settings.challenge.AskForManual = Settings.Core.Default.ChaPauseAndAskForManual;
			Helper.Settings.challenge.AutoUseDrink = Settings.Core.Default.AutoUseDrink;

			Helper.Settings.daily.DoCheck = Settings.Core.Default.DoDailyCheck;
			Helper.Settings.daily.DoShot = Settings.Core.Default.DoDailyShot;
		}

		internal static void SaveSettings() {
			Settings.GUI.Default.Save();
			Settings.Core.Default.Save();
		}

	}
}
