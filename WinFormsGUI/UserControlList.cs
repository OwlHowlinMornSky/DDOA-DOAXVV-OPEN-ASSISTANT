using System;
using System.Collections;
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

	public struct ListItemUserData {
		public uint coreTaskEnum;
		public int rank;
	}

	public partial class UserControlList : UserControl {

		private List<uint> m_listTasks = [];

		public UserControlList() {
			InitializeComponent();

			//flowLayoutPanel1.Controls.Clear();

		}

		public void SetList(List<uint> list) {
			flowLayoutPanel1.Controls.Clear();
			int cnt = 0;
			foreach (var i in list) {
				ListItemUserData data = new() {
					coreTaskEnum = i,
					rank = cnt
				};
				cnt++;

				var checkBox = new CheckBox() {
					DataContext = data,
					Width = 135,
					Text = "CB" + i,
				};
				checkBox.CheckedChanged += OnListCheckBoxChanged;
				checkBox.MouseEnter += OnListCheckBoxEnter;
				checkBox.MouseLeave += OnListCheckBoxLeave;
				flowLayoutPanel1.Controls.Add(checkBox);

				var radioBtn = new RadioButton() {
					DataContext = data,
					Width = 24,
					Height = 24,
					Image = Img.set0,
					Appearance = Appearance.Button,
				};
				radioBtn.CheckedChanged += OnListRadioBtnChanged;
				radioBtn.MouseEnter += OnListRadioBtnEnter;
				radioBtn.MouseLeave += OnListRadioBtnLeave;
				flowLayoutPanel1.Controls.Add(radioBtn);
				flowLayoutPanel1.SetFlowBreak(radioBtn, true);
			}
		}

		private void OnListCheckBoxChanged(object sender, EventArgs e) {
			var checkBox = (CheckBox)sender;
			var data = (ListItemUserData)checkBox.DataContext;
			int rank = data.rank;
			MessageBox.Show($"CheckBox #{rank} Changed to {checkBox.Checked}.");
		}

		private void OnListRadioBtnChanged(object sender, EventArgs e) {
			var radioBtn = (RadioButton)sender;
			var data = (ListItemUserData)radioBtn.DataContext;
			int rank = data.rank;
			MessageBox.Show($"RadioBtn #{rank} Changed to {radioBtn.Checked}.");
		}

		private void OnListCheckBoxEnter(object sender, EventArgs e) {
			var ctrl = (Control)sender;
			ctrl.BackColor = Color.LightBlue;
		}

		private void OnListCheckBoxLeave(object sender, EventArgs e) {
			var ctrl = (Control)sender;
			ctrl.BackColor = Color.Transparent;
		}

		private void OnListRadioBtnEnter(object sender, EventArgs e) {
			var ctrl = (Control)sender;
			flowLayoutPanel1.GetNextControl(ctrl, false).BackColor = Color.LightBlue;
		}

		private void OnListRadioBtnLeave(object sender, EventArgs e) {
			var ctrl = (Control)sender;
			flowLayoutPanel1.GetNextControl(ctrl, false).BackColor = Color.Transparent;
		}

		private void OnClickChooseAll(object sender, EventArgs e) {
			foreach (var ctrl in flowLayoutPanel1.Controls) {
				if (ctrl.GetType() == typeof(CheckBox)) {
					var checkBox = (CheckBox)ctrl;
					checkBox.Checked = true;
				}
			}
		}

		private void OnClickClearList(object sender, EventArgs e) {
			foreach (var ctrl in flowLayoutPanel1.Controls) {
				if (ctrl.GetType() == typeof(CheckBox)) {
					var checkBox = (CheckBox)ctrl;
					checkBox.Checked = false;
				}
			}
		}

		private void OnClickSortList(object sender, EventArgs args) {
		}

		private void UserControlList_Load(object sender, EventArgs e) {
			string str = Settings.GUI.Default.ListItems;
			var strs = str.Split(',');
			m_listTasks = [];
			foreach (var s in strs) {
				var n = uint.Parse(s);
				if (n > (uint)TaskEnumWrap.None)
					m_listTasks.Add(n);
			}
			SetList(m_listTasks);
		}

		/// <summary>
		/// 需要手动调用
		/// </summary>
		public void OnClose() {
			string str = "";
			str += (uint)TaskEnumWrap.None;
			foreach (var s in m_listTasks) {
				if (s > (uint)TaskEnumWrap.None) {
					str += ',';
					str += s;
				}
			}
		}
	}
}
