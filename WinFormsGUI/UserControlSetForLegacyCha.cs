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
	public partial class UserControlSetForLegacyCha : UserControl {
		public UserControlSetForLegacyCha() {
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
	}
}
