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

			SetStyle(ControlStyles.AllPaintingInWmPaint, true);
		}

		protected override void WndProc(ref Message m) {
			if (m.Msg == 0x0014) // 禁掉清除背景消息
				return;
			base.WndProc(ref m);
		}


		private void FormTest_Load(object sender, EventArgs e) {
			int n = 3;
			userControlLogger1.Log("RRSSF", Color.DarkRed);
			for (int i = 0; i < n; ++i) {

				userControlLogger1.Log("测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试\r\nyi\r\n二ereererererererer" + i);

			}


		}

		private void FormTest_FormClosed(object sender, FormClosedEventArgs e) {
			userControlList1.OnClose();

			Settings.GUI.Default.Save();
		}

		private void button1_Click(object sender, EventArgs e) {
			SuspendLayout();
			userControlLogger1.Log("测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试\r\nyi\r\n二ereererererererer");
			ResumeLayout();
		}
	}
}
