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
	public partial class UserControlSetForDaily : UserControl {
		public UserControlSetForDaily() {
			InitializeComponent();

			GlobalSetter.Regist.OnLockStepDaily += OnLockStep;
			if (GlobalSetter.Regist.LockedStepDaily)
				OnLockStep(true);
		}

		private void OnLockStep(bool isLock) {
			void f(bool locked) {
				Enabled = !locked;
			}
			if (InvokeRequired) {
				var r = BeginInvoke(f, isLock);
				EndInvoke(r);
			}
			else {
				f(isLock);
			}
		}

		private void UserControlSetForDaily_Load(object sender, EventArgs e) {
			checkBox_check.Checked = Settings.Core.Default.DoDailyCheck;
			checkBox_camShot.Checked = Settings.Core.Default.DoDailyShot;
		}

		private void CheckBox_check_CheckedChanged(object sender, EventArgs e) {
			Settings.Core.Default.DoDailyCheck = checkBox_check.Checked;
		}

		private void CheckBox_camShot_CheckedChanged(object sender, EventArgs e) {
			Settings.Core.Default.DoDailyShot = checkBox_camShot.Checked;
		}

	}
}
