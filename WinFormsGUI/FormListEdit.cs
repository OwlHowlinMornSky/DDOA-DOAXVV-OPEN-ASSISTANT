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
	public partial class FormListEdit : Form {

		private List<uint> m_listTasks = [];

		public List<uint> ListTasks {
			get {
				return m_listTasks;
			}
			set {
				m_listTasks = value;
				OnListSeted();
			}
		}

		public FormListEdit() {
			InitializeComponent();
		}

		private void OnListSeted() {
			listBox1.ClearSelected();
			listBox1.Items.Clear();
			foreach (var task in m_listTasks) {
				listBox1.Items.Add(
					Strings.Main.ResourceManager.GetString("Task" + task.ToString("000"))
				);
			}
		}

		private void button_add_Click(object sender, EventArgs e) {
			if (m_listTasks.Count >= (int)TaskEnumWrap.TaskMaxNum) {
				MessageBox.Show($"The limit of task length is {(int)TaskEnumWrap.TaskMaxNum}.");
				return;
			}
			var choose = new FormListEditChooseTask(((Button)sender).Text);
			var res = choose.ShowDialog();
			var choice = choose.choosedTask;
			if (res == DialogResult.Cancel || choice == (uint)TaskEnumWrap.None)
				return;
			m_listTasks.Add(choice);
			listBox1.Items.Add(
				Strings.Main.ResourceManager.GetString("Task" + choice.ToString("000"))
			);
		}

		private void button_Insert_Click(object sender, EventArgs e) {
			if (m_listTasks.Count >= (int)TaskEnumWrap.TaskMaxNum) {
				MessageBox.Show($"The limit of task length is {(int)TaskEnumWrap.TaskMaxNum}.");
				return;
			}
			var choose = new FormListEditChooseTask(((Button)sender).Text);
			var res = choose.ShowDialog();
			var choice = choose.choosedTask;
			if (res == DialogResult.Cancel || choice == (uint)TaskEnumWrap.None)
				return;
			var index = listBox1.SelectedIndex;
			m_listTasks.Insert(index + 1, choice);
			listBox1.Items.Insert(
				index + 1,
				Strings.Main.ResourceManager.GetString("Task" + choice.ToString("000"))
			);
		}

		private void button_modify_Click(object sender, EventArgs e) {
			var choose = new FormListEditChooseTask(((Button)sender).Text);
			var res = choose.ShowDialog();
			var choice = choose.choosedTask;
			if (res == DialogResult.Cancel || choice == (uint)TaskEnumWrap.None)
				return;
			var index = listBox1.SelectedIndex;
			m_listTasks[index] = choice;
			listBox1.Items[index] =
				Strings.Main.ResourceManager.GetString("Task" + choice.ToString("000"));
		}

		private void button_remove_Click(object sender, EventArgs e) {
			var index = listBox1.SelectedIndex;
			listBox1.Items.RemoveAt(index);
			m_listTasks.RemoveAt(index);
		}

		private void button_clearAll_Click(object sender, EventArgs e) {
			listBox1.ClearSelected();
			listBox1.Items.Clear();
			m_listTasks.Clear();
		}

		private void button_moveup_Click(object sender, EventArgs e) {
			var index = listBox1.SelectedIndex;
			if (index == 0)
				return;
			(m_listTasks[index - 1], m_listTasks[index]) =
				(m_listTasks[index], m_listTasks[index - 1]);
			(listBox1.Items[index - 1], listBox1.Items[index]) =
				(listBox1.Items[index], listBox1.Items[index - 1]);
			listBox1.SelectedIndex--;
		}

		private void button_movedown_Click(object sender, EventArgs e) {
			var index = listBox1.SelectedIndex;
			if (index == m_listTasks.Count - 1)
				return;
			(m_listTasks[index], m_listTasks[index + 1]) =
				(m_listTasks[index + 1], m_listTasks[index]);
			(listBox1.Items[index], listBox1.Items[index + 1]) =
				(listBox1.Items[index + 1], listBox1.Items[index]);
			listBox1.SelectedIndex++;
		}

		private void listBox1_SelectedIndexChanged(object sender, EventArgs e) {
			if (listBox1.SelectedIndex != -1) {
				button_Insert.Enabled = true;
				button_modify.Enabled = true;
				button_remove.Enabled = true;
				button_moveup.Enabled = true;
				button_movedown.Enabled = true;
			}
			else {
				button_Insert.Enabled = false;
				button_modify.Enabled = false;
				button_remove.Enabled = false;
				button_moveup.Enabled = false;
				button_movedown.Enabled = false;
			}
		}
	}
}
