namespace WinFormsGUI.SettingsPage {
	partial class UserControlSettingsCtrl {
		/// <summary> 
		/// 必需的设计器变量。
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary> 
		/// 清理所有正在使用的资源。
		/// </summary>
		/// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
		protected override void Dispose(bool disposing) {
			if (disposing && (components != null)) {
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region 组件设计器生成的代码

		/// <summary> 
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		private void InitializeComponent() {
			gpBox_CtrlSet = new GroupBox();
			radioBtn_CtrlInput = new RadioButton();
			radioBtn_CtrlMsg = new RadioButton();
			checkBox_Hook = new CheckBox();
			gpBox_CtrlSet.SuspendLayout();
			SuspendLayout();
			// 
			// gpBox_CtrlSet
			// 
			gpBox_CtrlSet.Anchor = AnchorStyles.Top | AnchorStyles.Left | AnchorStyles.Right;
			gpBox_CtrlSet.Controls.Add(radioBtn_CtrlInput);
			gpBox_CtrlSet.Controls.Add(radioBtn_CtrlMsg);
			gpBox_CtrlSet.Location = new Point(3, 3);
			gpBox_CtrlSet.Name = "gpBox_CtrlSet";
			gpBox_CtrlSet.Size = new Size(261, 80);
			gpBox_CtrlSet.TabIndex = 12;
			gpBox_CtrlSet.TabStop = false;
			gpBox_CtrlSet.Text = "鼠标控制方式";
			// 
			// radioBtn_CtrlInput
			// 
			radioBtn_CtrlInput.AutoSize = true;
			radioBtn_CtrlInput.ImeMode = ImeMode.NoControl;
			radioBtn_CtrlInput.Location = new Point(6, 49);
			radioBtn_CtrlInput.Name = "radioBtn_CtrlInput";
			radioBtn_CtrlInput.Size = new Size(98, 21);
			radioBtn_CtrlInput.TabIndex = 1;
			radioBtn_CtrlInput.Text = "发送鼠标输入";
			radioBtn_CtrlInput.UseVisualStyleBackColor = true;
			radioBtn_CtrlInput.CheckedChanged += RadioBtn_CtrlInput_CheckedChanged;
			// 
			// radioBtn_CtrlMsg
			// 
			radioBtn_CtrlMsg.AutoSize = true;
			radioBtn_CtrlMsg.Checked = true;
			radioBtn_CtrlMsg.ImeMode = ImeMode.NoControl;
			radioBtn_CtrlMsg.Location = new Point(6, 22);
			radioBtn_CtrlMsg.Name = "radioBtn_CtrlMsg";
			radioBtn_CtrlMsg.Size = new Size(98, 21);
			radioBtn_CtrlMsg.TabIndex = 0;
			radioBtn_CtrlMsg.TabStop = true;
			radioBtn_CtrlMsg.Text = "发送窗口消息";
			radioBtn_CtrlMsg.UseVisualStyleBackColor = true;
			radioBtn_CtrlMsg.CheckedChanged += RadioBtn_CtrlMsg_CheckedChanged;
			// 
			// checkBox_Hook
			// 
			checkBox_Hook.AutoSize = true;
			checkBox_Hook.Location = new Point(3, 89);
			checkBox_Hook.Name = "checkBox_Hook";
			checkBox_Hook.Size = new Size(248, 21);
			checkBox_Hook.TabIndex = 13;
			checkBox_Hook.Text = "拦截用户的光标消息（按住CTRL时免除）";
			checkBox_Hook.UseVisualStyleBackColor = true;
			checkBox_Hook.CheckedChanged += CheckBox_Hook_CheckedChanged;
			// 
			// UserControlSettingsCtrl
			// 
			AutoScaleDimensions = new SizeF(7F, 17F);
			AutoScaleMode = AutoScaleMode.Font;
			Controls.Add(checkBox_Hook);
			Controls.Add(gpBox_CtrlSet);
			Name = "UserControlSettingsCtrl";
			Size = new Size(267, 376);
			Load += UserControlSettingsCtrl_Load;
			gpBox_CtrlSet.ResumeLayout(false);
			gpBox_CtrlSet.PerformLayout();
			ResumeLayout(false);
			PerformLayout();
		}

		#endregion
		private GroupBox gpBox_CtrlSet;
		private RadioButton radioBtn_CtrlInput;
		private RadioButton radioBtn_CtrlMsg;
		private CheckBox checkBox_Hook;
	}
}
