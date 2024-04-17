using Wrapper;

namespace WinFormsGUI {
	public partial class UserControlHome : UserControl {
		public UserControlHome() {
			InitializeComponent();

			userControlList1.SetSelectedChangedTo = ChangeSettingCallback;

			SetStyle(ControlStyles.AllPaintingInWmPaint, true);
		}

		protected override void WndProc(ref Message m) {
			if (m.Msg == 0x0014) // 禁掉清除背景消息
				return;
			base.WndProc(ref m);
		}

		private void ChangeSetting(uint id) {
			panel1.Controls.Clear();
			switch ((TaskEnumWrap)id) {
			default:
			case TaskEnumWrap.None:
				panel1.Controls.Add(new UserControlSetForDefault() {
					Dock = DockStyle.Fill,
				});
				break;
			case TaskEnumWrap.LegacyCha:
				panel1.Controls.Add(new UserControlSetForLegacyCha() { 
					Dock = DockStyle.Fill,
				});
				break;
			}
		}

		private void ChangeSettingCallback(ListItemUserData data) {
			if (InvokeRequired) {
				var r = BeginInvoke(new Action(() => {
					ChangeSetting(data.coreTaskEnum);
				}));
				EndInvoke(r);
			}
			else {
				ChangeSetting(data.coreTaskEnum);
			}
		}

		public void ClearLog() => userControlLogger1.Clear();
		public void Log(string message, Color color) => userControlLogger1.Log(message, color);
		public void Log(string message) => userControlLogger1.Log(message);

		private void UserControlHome_Load(object sender, EventArgs e) {
			SetListMiddle();
		}

		public void OnClose() {
			userControlList1.OnClose();
		}

		private void SetListMiddle() {
			userControlList1.Left = (panel2.Width - userControlList1.Width) / 2;
			button1.Left = (panel2.Width - button1.Width) / 2;
		}

		private void panel2_SizeChanged(object sender, EventArgs e) {
			SetListMiddle();
		}

		private void button1_Click(object sender, EventArgs e) {
			ClearLog();
			//Log("测试测试测试测试测试测试测试测试测试测试测试测试测试测试测试\r\nyi\r\n二ereererererererer");
		}
	}
}
