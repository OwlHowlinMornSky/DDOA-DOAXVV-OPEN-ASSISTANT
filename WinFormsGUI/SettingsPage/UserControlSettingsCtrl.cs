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

namespace WinFormsGUI.SettingsPage {
	public partial class UserControlSettingsCtrl : UserControl {
		public UserControlSettingsCtrl() {
			InitializeComponent();
			// 注册以在工作时锁定控件。
			WorkStatusLocker.lockAction += OnWorkLockAndUnlock;
			if (WorkStatusLocker.Locked)
				OnWorkLockAndUnlock(true);
		}

		~UserControlSettingsCtrl() {
			WorkStatusLocker.lockAction -= OnWorkLockAndUnlock;
		}

		/// <summary>
		/// 监听工作状态改变锁定控件的事件
		/// </summary>
		private void OnWorkLockAndUnlock(bool isLock) {
			Enabled = !isLock;
		}


		private void UserControlSettingsCtrl_Load(object sender, EventArgs e) {
			radioBtn_CtrlInput.Checked = Settings.Core.Default.CtrlSendInput;
			checkBox_Hook.Checked = Settings.Core.Default.UseHook;
		}

		private void RadioBtn_CtrlMsg_CheckedChanged(object sender, EventArgs e) {
			Settings.Core.Default.CtrlSendInput = false;
			Program.helper.SetMouseSendInputOrSendMessage(false);
		}

		private void RadioBtn_CtrlInput_CheckedChanged(object sender, EventArgs e) {
			Settings.Core.Default.CtrlSendInput = true;
			Program.helper.SetMouseSendInputOrSendMessage(true);
		}

		private void CheckBox_Hook_CheckedChanged(object sender, EventArgs e) {
			Settings.Core.Default.UseHook = checkBox_Hook.Checked;
			Program.helper.SetUseHook(checkBox_Hook.Checked);
		}

	}
}
