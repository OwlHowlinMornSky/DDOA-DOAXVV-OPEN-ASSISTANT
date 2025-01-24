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
	public partial class UserControlSetForChallenge : UserControl {
		public UserControlSetForChallenge() {
			InitializeComponent();

			GlobalSetter.Regist.OnLockStepChallenge += OnLockStep;
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

		private void MatchSet_RadioBtn_CheckedChanged(object sender, EventArgs e) {
			if (radioBtn_PreviousMatch.Checked) {
				Settings.Core.Default.PlayMatchType = 0;
			}
			else if (radioBtn_NewMatch.Checked) {
				Settings.Core.Default.PlayMatchType = 1;
			}
			else {
				Settings.Core.Default.PlayMatchType = 2;
			}
		}

		private void AwardMatch_RadioBtn_CheckedChanged(object sender, EventArgs e) {
			if (radioBtn_AwardNo.Checked) {
				Settings.Core.Default.AwardMatch = 0;
			}
			else if (radioBtn_AwardPlay.Checked) {
				Settings.Core.Default.AwardMatch = 1;
			}
			else {
				Settings.Core.Default.AwardMatch = 2;
			}
		}

		private void UserControlSetForLegacyCha_Load(object sender, EventArgs e) {
			switch (Settings.Core.Default.PlayMatchType) {
			case 1:
				radioBtn_NewMatch.Checked = true;
				break;
			case 2:
				radioButton_activity.Checked = true;
				break;
			default:
				radioBtn_PreviousMatch.Checked = true;
				break;
			}
			switch (Settings.Core.Default.AwardMatch) {
			case 1:
				radioBtn_AwardPlay.Checked = true;
				break;
			case 2:
				radioBtn_AwardIgnore.Checked = true;
				break;
			default:
				radioBtn_AwardNo.Checked = true;
				break;
			}

			checkBox_useCamFP.Checked = Settings.Core.Default.AutoUseCamFp;
			checkBox_PauseForMannual.Checked = Settings.Core.Default.ChaPauseAndAskForManual;
			checkBox_autoUseDrink.Checked = Settings.Core.Default.AutoUseDrink;

			comboBox1.SelectedIndex = Settings.Core.Default.PlayLevel;
			numericUpDown1.Value = Settings.Core.Default.PlayLevelR;
		}

		private void CheckBox_useCamFP_CheckedChanged(object sender, EventArgs e) {
			Settings.Core.Default.AutoUseCamFp = checkBox_useCamFP.Checked;
		}

		private void CheckBox_PauseForMannual_CheckedChanged(object sender, EventArgs e) {
			Settings.Core.Default.ChaPauseAndAskForManual = checkBox_PauseForMannual.Checked;
		}

		private void CheckBox_autoUseDrink_CheckedChanged(object sender, EventArgs e) {
			Settings.Core.Default.AutoUseDrink = checkBox_autoUseDrink.Checked;
		}

		private void comboBox1_SelectedValueChanged(object sender, EventArgs e) {
			Settings.Core.Default.PlayLevel = comboBox1.SelectedIndex;
			numericUpDown1.Maximum = Settings.Core.Default.PlayLevel switch {
				// E,D,   C,   B,   A
				1 or 2 or 3 or 4 or 5 => 8,
				// S
				6 => 8,
				_ => 1,
			};
		}

		private void numericUpDown1_ValueChanged(object sender, EventArgs e) {
			Settings.Core.Default.PlayLevelR = (int)numericUpDown1.Value;
		}
	}
}
