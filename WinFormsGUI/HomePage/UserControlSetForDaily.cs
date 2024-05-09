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
	public partial class UserControlSetForDaily : UserControl {
		public UserControlSetForDaily() {
			InitializeComponent();
		}

		private void UserControlSetForDaily_Load(object sender, EventArgs e) {
			 checkBox_check.Checked = Settings.Core.Default.DoDailyCheck;
			 checkBox_camShot.Checked = Settings.Core.Default.DoDailyShot;
		}

		private void CheckBox_check_CheckedChanged(object sender, EventArgs e) {
			Settings.Core.Default.DoDailyCheck = checkBox_check.Checked;
			Program.helper.SetDoDailyCheck(Settings.Core.Default.DoDailyCheck);
		}

		private void CheckBox_camShot_CheckedChanged(object sender, EventArgs e) {
			Settings.Core.Default.DoDailyShot = checkBox_camShot.Checked;
			Program.helper.SetDoDailyShot(Settings.Core.Default.DoDailyShot);
		}

	}
}
