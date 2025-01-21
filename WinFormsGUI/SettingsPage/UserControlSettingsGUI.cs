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
	public partial class UserControlSettingsGUI : UserControl {
		public UserControlSettingsGUI() {
			InitializeComponent();
		}

		private void UserControlSettingsGUI_Load(object sender, EventArgs e) {
			chkBox_SetHideToTray.Checked = Settings.GUI.Default.HideToTray;
			chkBox_SetNotify.Checked = Settings.GUI.Default.UseNotify;
			chkBox_SetDisableClose.Checked = Settings.GUI.Default.DisableClose;
		}

		private void ChkBox_SetDisableClose_CheckedChanged(object sender, EventArgs e) {
			Settings.GUI.Default.DisableClose = chkBox_SetDisableClose.Checked;
		}

		private void ChkBox_SetHideToTray_CheckedChanged(object sender, EventArgs e) {
			Settings.GUI.Default.HideToTray = chkBox_SetHideToTray.Checked;
		}

		private void ChkBox_SetNotify_CheckedChanged(object sender, EventArgs e) {
			Settings.GUI.Default.UseNotify = chkBox_SetNotify.Checked;
		}
	}
}
