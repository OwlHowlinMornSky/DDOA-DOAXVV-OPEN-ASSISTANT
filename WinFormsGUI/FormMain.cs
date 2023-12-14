using System.Windows.Forms;
using Wrapper;

namespace WinFormsGUI {
	public partial class FormMain : Form {
		#region ==========Members==========
		private HelperWrapper m_helper = new();
		private bool m_btnMainIsStart = true;
		#endregion

		#region ==========Common===========
		public FormMain() {
			InitializeComponent();
		}

		public void Log(string msg) {
			bool scroll = listBox_Main.TopIndex == listBox_Main.Items.Count - (int)(listBox_Main.Height / listBox_Main.ItemHeight);
			listBox_Main.Items.Add(msg);
			if (scroll)
				listBox_Main.TopIndex = listBox_Main.Items.Count - (int)(listBox_Main.Height / listBox_Main.ItemHeight);
		}

		public void Log() {
			bool scroll = listBox_Main.TopIndex == listBox_Main.Items.Count - (int)(listBox_Main.Height / listBox_Main.ItemHeight);
			listBox_Main.Items.Add("");
			if (scroll)
				listBox_Main.TopIndex = listBox_Main.Items.Count - (int)(listBox_Main.Height / listBox_Main.ItemHeight);
		}
		#endregion

		#region ==========Events===========
		#region ---------MainForm----------
		public void FormMain_Load(object sender, EventArgs e) {
			button_Tab0_Main.Text = Strings.str.Main_Btn_Start;

			if (Settings.main.Default.Game_ForNew)
				radioButton_Tab0_Box0_1.Checked = true;
			if (Settings.main.Default.Ctrl_ForMouse)
				radioButton_Tab0_Box1_1.Checked = true;
		}

		private void FormMain_FormClosing(object sender, FormClosingEventArgs e) {
			m_helper.askForStop();

			Settings.main.Default.Game_ForNew = radioButton_Tab0_Box0_1.Checked;
			Settings.main.Default.Ctrl_ForMouse = radioButton_Tab0_Box1_1.Checked;

			Settings.main.Default.Save();

			while (m_helper.isRunning()) {
				Thread.Sleep(30);
			}
		}

		private void FormMain_FormClosed(object sender, FormClosedEventArgs e) {
			Settings.main.Default.Save();
		}
		#endregion
		#region -----------Tab0------------
		private void button_Tab0_Main_Click(object sender, EventArgs e) {
			groupBox_Tab0_Box0.Enabled = false;
			groupBox_Tab0_Box1.Enabled = false;
			button_Tab0_Main.Enabled = false;
			if (m_btnMainIsStart) {
				listBox_Main.Items.Clear();

				if (!m_helper.start()) {
					listBox_Main.Items.Add("无法启动任务");
					return;
				}
				timer1.Enabled = true;
			}
			else {
				m_helper.askForStop();
			}
		}

		private void radioButton_Tab0_Box0_0_CheckedChanged(object sender, EventArgs e) {
			if (radioButton_Tab0_Box0_0.Checked)
				m_helper.regForNew(false);
		}

		private void radioButton_Tab0_Box0_1_CheckedChanged(object sender, EventArgs e) {
			if (radioButton_Tab0_Box0_1.Checked)
				m_helper.regForNew(true);
		}

		private void radioButton_Tab0_Box1_0_CheckedChanged(object sender, EventArgs e) {
			if (radioButton_Tab0_Box1_0.Checked)
				m_helper.regForMouse(false);
		}

		private void radioButton_Tab0_Box1_1_CheckedChanged(object sender, EventArgs e) {
			if (radioButton_Tab0_Box1_1.Checked)
				m_helper.regForMouse(true);
		}
		#endregion
		private void timer1_Tick(object sender, EventArgs e) {
			ReturnMessage m = m_helper.msgPop();
			switch (m) {
			case ReturnMessage.Stopped:
				Log("已停止");
				groupBox_Tab0_Box0.Enabled = true;
				groupBox_Tab0_Box1.Enabled = true;
				timer1.Enabled = false;
				break;
			case ReturnMessage.BtnToStop:
				button_Tab0_Main.Text = Strings.str.Main_Btn_Stop;
				button_Tab0_Main.Enabled = true;
				m_btnMainIsStart = false;
				break;
			case ReturnMessage.BtnToStart:
				button_Tab0_Main.Text = Strings.str.Main_Btn_Start;
				button_Tab0_Main.Enabled = true;
				m_btnMainIsStart = true;
				break;
			case ReturnMessage.Log_ErrorIsRunning:
				Log("不能重复运行任务");
				break;
			case ReturnMessage.Log_Stopping:
				Log("正在停止...");
				break;
			case ReturnMessage.Log_ErrorNotFindWnd:
				Log("找不到DOAXVV窗口");
				break;
			case ReturnMessage.Log_ErrorCannotCapture:
				Log("无法截图");
				break;
			case ReturnMessage.Log_ErrorInWork:
				Log();
				Log("工作异常");
				MessageBox.Show(this, "工作异常", "任务出错", MessageBoxButtons.OK, MessageBoxIcon.Error);
				break;
			case ReturnMessage.Log_ErrorInTask:
				Log();
				Log("任务出错");
				break;

			case ReturnMessage.Log_Challenge_Start:
				Log("任务开始: 挑战赛");
				break;
			case ReturnMessage.Log_Challenge_BeginNum: // 挑战赛开始（下跟次数！）
				Log("开始第 " + m_helper.codePop() + " 次比赛");
				break;
			case ReturnMessage.Log_Challenge_EnterLast:
				Log("进入上一次比赛");
				break;
			case ReturnMessage.Log_Challenge_EnterNew:
				Log("进入新比赛");
				break;
			case ReturnMessage.Log_Challenge_Play:
				Log("开始挑战");
				break;
			case ReturnMessage.Log_Challenge_WaitForEnd:
				Log("等待结算");
				break;
			case ReturnMessage.Log_Challenge_End:
				Log("挑战结束");
				break;
			case ReturnMessage.Log_Challenge_Quiting:
				Log("正在退出比赛");
				break;
			case ReturnMessage.Log_Challenge_Over:
				Log("比赛结束");
				break;
			case ReturnMessage.Log_Challenge_Exit:
				Log("任务结束: 挑战赛");
				break;

			case ReturnMessage.Log_Task_Stop:
				Log("任务中止");
				break;
			case ReturnMessage.Log_Task_Exception:
				Log("任务异常");
				MessageBox.Show(this, "任务异常", "任务出错", MessageBoxButtons.OK, MessageBoxIcon.Error);
				break;

			case ReturnMessage.Log_Task_Challenge_NoNew:
				Log("找不到新比赛");
				break;
			case ReturnMessage.Log_Task_Challenge_NoLast:
				Log("找不到上一次比赛");
				break;
			case ReturnMessage.Log_Task_Challenge_NoEnter:
				Log("无法进入比赛");
				break;
			case ReturnMessage.Log_Task_Challenge_LowFP:
				Log("FP耗尽");
				break;
			case ReturnMessage.Log_Task_Challenge_NoStart:
				Log("无法开始挑战");
				break;
			case ReturnMessage.Log_Task_Challenge_TimeOut:
				Log("挑战超时");
				break;
			case ReturnMessage.Log_Task_Challenge_NoEnd:
				Log("无法退出挑战");
				break;
			case ReturnMessage.Log_Task_Challenge_NoOver:
				Log("无法退出比赛");
				break;
			}
			return;
		}
		#endregion
	}
}
