/*
*    DDOA-DOAXVV-OPEN-ASSISTANT
* 
*     Copyright 2023-2024  Tyler Parret True
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
	public partial class UserControlSettings : UserControl {

		private int listSelectedIndex = -1;

		public UserControlSettings() {
			InitializeComponent();
		}

		private void UserControlSettings_Load(object sender, EventArgs e) {
		}

		private void ListBox1_SelectedIndexChanged(object sender, EventArgs e) {
			var listBox = sender as ListBox;
			var index = listBox.SelectedIndex;
			if (listSelectedIndex == index)
				return;
			listSelectedIndex = index;
			panel1.SuspendLayout();
			panel1.Controls.Clear();
			Control ctrl;
			switch (index) {
			case 0:
				ctrl = new SettingsPage.UserControlSettingsGUI();
				break;
			case 1:
				ctrl = new SettingsPage.UserControlSettingsWork();
				break;
			case 2:
				ctrl = new SettingsPage.UserControlSettingsCtrl();
				break;
			default:
				return;
			}
			ctrl.Dock = DockStyle.Fill;
			panel1.Controls.Add(ctrl);
			panel1.ResumeLayout();
			return;
		}
	}
}
