using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Wrapper;

namespace WinFormsGUI {
	public partial class FormListEditChooseTask : Form {

		public uint choosedTask = (uint)TaskEnumWrap.None;

		public FormListEditChooseTask(string TipText) {
			InitializeComponent();
			Text += TipText;
		}

		private void FormListEditChooseTask_Load(object sender, EventArgs e) {
			for (uint i = (uint)TaskEnumWrap.None + 1, n = (uint)TaskEnumWrap.COUNT;
				i < n;
				i++) {
				listBox1.Items.Add(Strings.Main.ResourceManager.GetString("Task" + i.ToString("000")));
			}
		}

		private void listBox1_SelectedIndexChanged(object sender, EventArgs e) {
			if (listBox1.SelectedIndex == -1)
				choosedTask = (uint)TaskEnumWrap.None;
			else
				choosedTask = (uint)listBox1.SelectedIndex - (uint)TaskEnumWrap.None + 1;
		}

		private void button1_Click(object sender, EventArgs e) {
			DialogResult = DialogResult.OK;
		}

		private void button2_Click(object sender, EventArgs e) {
			choosedTask = (uint)TaskEnumWrap.None;
			DialogResult = DialogResult.Cancel;
		}
	}
}
