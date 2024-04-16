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
			int n = 30;
			userControlLogger1.Log("RRSSF", Color.DarkRed);
			for (int i = 0; i < n; ++i) {

				userControlLogger1.Log("测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试\r\nyi\r\n二ereererererererer" + i);

			}


		}

		private void FormTest_FormClosed(object sender, FormClosedEventArgs e) {
			userControlList1.OnClose();

			Settings.GUI.Default.Save();
		}

	}
}
