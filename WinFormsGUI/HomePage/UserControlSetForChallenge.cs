﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinFormsGUI {
	public partial class UserControlSetForChallenge : UserControl {
		public UserControlSetForChallenge() {
			InitializeComponent();
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
			Program.helper.SetChallengeMatch(Settings.Core.Default.PlayMatchType);
		}

		private void AwardMatch_RadioBtn_CheckedChanged(object sender, EventArgs e) {
			Program.helper.SetChallengeCheckAwardOrNot(!radioBtn_AwardNo.Checked);
			Program.helper.SetChallengePlayAwardOrNot(radioBtn_AwardPlay.Checked);
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
			Program.helper.SetUseCamFP(Settings.Core.Default.AutoUseCamFp);
		}

		private void CheckBox_PauseForMannual_CheckedChanged(object sender, EventArgs e) {
			Settings.Core.Default.ChaPauseAndAskForManual = checkBox_PauseForMannual.Checked;
			Program.helper.SetChaAskForManual(Settings.Core.Default.ChaPauseAndAskForManual);
		}

		private void CheckBox_autoUseDrink_CheckedChanged(object sender, EventArgs e) {
			Settings.Core.Default.AutoUseDrink = checkBox_autoUseDrink.Checked;
			Program.helper.SetChaAutoUseDrink(Settings.Core.Default.AutoUseDrink);
		}

		private void comboBox1_SelectedValueChanged(object sender, EventArgs e) {
			Settings.Core.Default.PlayLevel = comboBox1.SelectedIndex;
			switch (Settings.Core.Default.PlayLevel) {
			case 1: // E
			case 2: // D
			case 3: // C
			case 4: // B
			case 5: // A
				numericUpDown1.Maximum = 8;
				break;
			case 6: // S
				numericUpDown1.Maximum = 8;
				break;
			default:
				numericUpDown1.Maximum = 1;
				break;
			}
		}

		private void numericUpDown1_ValueChanged(object sender, EventArgs e) {
			Settings.Core.Default.PlayLevelR = (int)numericUpDown1.Value;
		}
	}
}
