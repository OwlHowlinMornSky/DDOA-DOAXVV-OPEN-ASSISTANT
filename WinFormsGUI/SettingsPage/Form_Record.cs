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

		//private bool m_started = false;

		private void button1_Click(object sender, EventArgs e) {
			var code = Program.helper.StartRecord();
			if (code != 0) {
				MessageBox.Show(code.ToString(), "Record Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
				return;
			}
			//m_started = true;
			button1.Enabled = false;
			button2.Enabled = true;
		}

		private void button2_Click(object sender, EventArgs e) {
			var code = Program.helper.StopRecord();
			if (code != 0) {
				MessageBox.Show(code.ToString(), "Record Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
				//return;
			}
			//m_started = false;
			button1.Enabled = true;
			button2.Enabled = false;
			if (code == 0) {
				saveFileDialog1.ShowDialog(this);
			}
		}

		private void Form_Record_Load(object sender, EventArgs e) {
			button2.Enabled = false;
		}

		private void saveFileDialog1_FileOk(object sender, CancelEventArgs e) {
			File.Move("records/temporary.ddoa", saveFileDialog1.FileName);
		}
	}
}
