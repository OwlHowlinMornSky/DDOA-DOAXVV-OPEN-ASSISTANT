using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinFormsGUI.SettingsPage {
	public partial class Form_Record : Form {
		public Form_Record() {
			InitializeComponent();
		}

		private StreamWriter m_fs;

		private void button1_Click(object sender, EventArgs e) {
			var code = Program.helper.StartRecord(Handle);
			if (code != 0) {
				MessageBox.Show(code.ToString(), "Record Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
				return;
			}
			m_fs = new StreamWriter("records/temporary.ddoa");
			if (m_fs == null) {
				m_fs.Close();
				MessageBox.Show(code.ToString(), "Record Not Available", MessageBoxButtons.OK, MessageBoxIcon.Error);
				return;
			}
			m_fs.WriteLine("start");

			button1.Enabled = false;
			button2.Enabled = true;
		}

		private void button2_Click(object sender, EventArgs e) {
			var code = Program.helper.StopRecord();
			if (code != 0) {
				MessageBox.Show(code.ToString(), "Record Failed", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
			button1.Enabled = true;
			button2.Enabled = false;

			m_fs.WriteLine("stop");
			m_fs.Close();

			if (code == 0) {
				saveFileDialog1.InitialDirectory = Path.Combine(Directory.GetCurrentDirectory(), "records");
				saveFileDialog1.ShowDialog(this);
			}
		}

		private void Form_Record_Load(object sender, EventArgs e) {
			button2.Enabled = false;
		}

		private void saveFileDialog1_FileOk(object sender, CancelEventArgs e) {
			File.Move("records/temporary.ddoa", saveFileDialog1.FileName);
		}

		protected override void WndProc(ref Message m) {
			if (m.Msg == 0x8000 + 0x0233) {
				switch (m.WParam) {
				case 1:
					m_fs.WriteLine($"sleep {m.LParam.ToInt64()}");
					break;
				case 2:
					m_fs.WriteLine($"move {m.LParam & 0xffff} {(m.LParam >> 16) & 0xffff}");
					break;
				case 3:
					m_fs.WriteLine("click");
					break;
				case 4:
					m_fs.WriteLine($"wheel {m.LParam.ToInt32()}");
					break;
				}
			}
			else {
				base.WndProc(ref m);
			}
			return;
		}

	}
}
