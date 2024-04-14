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
	public partial class UserControlList : UserControl {
		public UserControlList() {
			InitializeComponent();
			int n = 5;

			for (int i = 0; i < n; ++i) {
				var checkBox = new CheckBox() {
					Text = "CB" + i,
					//Height = 36,
					DataContext = i
				};
				checkBox.CheckStateChanged += OnListCheckBoxChanged;
				checkBox.MouseEnter += OnListCheckBoxEnter;
				checkBox.MouseLeave += OnListCheckBoxLeave;
				flowLayoutPanel1.Controls.Add(checkBox);

				var radioBtn = new RadioButton() {
					DataContext = i,
					Image = Img.set0,
					Width = 24,
					Height = 24,
					Appearance = Appearance.Button,
				};
				radioBtn.CheckedChanged += OnListRadioBtnChanged;
				radioBtn.MouseEnter += OnListRadioBtnEnter;
				radioBtn.MouseLeave += OnListRadioBtnLeave;
				flowLayoutPanel1.Controls.Add(radioBtn);
				flowLayoutPanel1.SetFlowBreak(radioBtn, true);
			}

			//flowLayoutPanel1.Controls.Clear();

		}

		~UserControlList() {
			//flowLayoutPanel1.Controls.Clear();
		}


		private void OnListCheckBoxChanged(object sender, EventArgs e) {
			//if (sender == null || sender.GetType() != typeof(CheckBox)) {
			//	return;
			//}
			var checkBox = (CheckBox)sender;
			var data = checkBox.DataContext;
			//if (data == null || data.GetType() != typeof(int)) {
			//	return;
			//}
			var num = (int)data;
			//MessageBox.Show($"Check Box #{num} Changed to {checkBox.CheckState}.");
		}

		private void OnListRadioBtnChanged(object sender, EventArgs e) {
			//if (sender == null || sender.GetType() != typeof(Button)) {
			//	return;
			//}
			var btn = (RadioButton)sender;
			var data = btn.DataContext;
			//if (data == null || data.GetType() != typeof(int)) {
			//	return;
			//}
			var num = (int)data;
			//if (btn.Checked == true)
			//	btn.Image = Img.set1;
			//else
			//	btn.Image = Img.set0;
			//MessageBox.Show($"RadioButton #{num} Clicked.");
		}

		private void OnListCheckBoxEnter(object sender, EventArgs e) {
			var ctrl = (Control)sender;
			ctrl.BackColor = Color.LightBlue;
		}

		private void OnListCheckBoxLeave(object sender, EventArgs e) {
			var ctrl = (Control)sender;
			ctrl.BackColor = CheckBox.DefaultBackColor;
		}

		private void OnListRadioBtnEnter(object sender, EventArgs e) {
			var ctrl = (Control)sender;
			flowLayoutPanel1.GetNextControl(ctrl, false).BackColor = Color.LightBlue;
		}

		private void OnListRadioBtnLeave(object sender, EventArgs e) {
			var ctrl = (Control)sender;
			flowLayoutPanel1.GetNextControl(ctrl, false).BackColor = CheckBox.DefaultBackColor;
		}
	}
}
