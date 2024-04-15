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
	public partial class FormTest : Form {
		public FormTest() {
			InitializeComponent();


		}

		private void FormTest_Load(object sender, EventArgs e) {

			flowLayoutPanel1.Controls.Add(new Label {
				Text = "12345"
			});
			flowLayoutPanel1.Controls.Add(new Label {
				Text = "一\r\n测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试\r\n二",
				//AutoEllipsis = true,
				AutoSize = true,
				MaximumSize = new Size(123, 0)
			});

		}

		private void FormTest_FormClosed(object sender, FormClosedEventArgs e) {
			userControlList1.OnClose();

			Settings.GUI.Default.Save();
		}
	}
}
