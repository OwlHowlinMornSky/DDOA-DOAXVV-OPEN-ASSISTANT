using System;
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
			Program.helper.SetChallengeForNewOrLast(radioBtn_NewMatch.Checked);
			Settings.Core.Default.PlayNewMatch = radioBtn_NewMatch.Checked;
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
			radioBtn_NewMatch.Checked = Settings.Core.Default.PlayNewMatch;

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
		}
	}
}
