namespace WinFormsGUI.SettingsPage {
	partial class UserControlSettingsGUI {
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
			chkBox_SetDisableClose = new CheckBox();
			chkBox_SetNotify = new CheckBox();
			chkBox_SetHideToTray = new CheckBox();
			SuspendLayout();
			// 
			// chkBox_SetDisableClose
			// 
			chkBox_SetDisableClose.AutoSize = true;
			chkBox_SetDisableClose.ImeMode = ImeMode.NoControl;
			chkBox_SetDisableClose.Location = new Point(3, 3);
			chkBox_SetDisableClose.Name = "chkBox_SetDisableClose";
			chkBox_SetDisableClose.Size = new Size(123, 21);
			chkBox_SetDisableClose.TabIndex = 13;
			chkBox_SetDisableClose.Text = "禁用窗口关闭按钮";
			chkBox_SetDisableClose.UseVisualStyleBackColor = true;
			chkBox_SetDisableClose.CheckedChanged += ChkBox_SetDisableClose_CheckedChanged;
			// 
			// chkBox_SetNotify
			// 
			chkBox_SetNotify.AutoSize = true;
			chkBox_SetNotify.ImeMode = ImeMode.NoControl;
			chkBox_SetNotify.Location = new Point(3, 57);
			chkBox_SetNotify.Name = "chkBox_SetNotify";
			chkBox_SetNotify.Size = new Size(75, 21);
			chkBox_SetNotify.TabIndex = 14;
			chkBox_SetNotify.Text = "发送通知";
			chkBox_SetNotify.UseVisualStyleBackColor = true;
			chkBox_SetNotify.CheckedChanged += ChkBox_SetNotify_CheckedChanged;
			// 
			// chkBox_SetHideToTray
			// 
			chkBox_SetHideToTray.AutoSize = true;
			chkBox_SetHideToTray.ImeMode = ImeMode.NoControl;
			chkBox_SetHideToTray.Location = new Point(3, 30);
			chkBox_SetHideToTray.Name = "chkBox_SetHideToTray";
			chkBox_SetHideToTray.Size = new Size(123, 21);
			chkBox_SetHideToTray.TabIndex = 15;
			chkBox_SetHideToTray.Text = "最小化隐藏到托盘";
			chkBox_SetHideToTray.UseVisualStyleBackColor = true;
			chkBox_SetHideToTray.CheckedChanged += ChkBox_SetHideToTray_CheckedChanged;
			// 
			// UserControlSettingsGUI
			// 
			AutoScaleDimensions = new SizeF(7F, 17F);
			AutoScaleMode = AutoScaleMode.Font;
			Controls.Add(chkBox_SetHideToTray);
			Controls.Add(chkBox_SetNotify);
			Controls.Add(chkBox_SetDisableClose);
			Name = "UserControlSettingsGUI";
			Size = new Size(261, 309);
			Load += UserControlSettingsGUI_Load;
			ResumeLayout(false);
			PerformLayout();
		}

		#endregion

		private CheckBox chkBox_SetDisableClose;
		private CheckBox chkBox_SetNotify;
		private CheckBox chkBox_SetHideToTray;
	}
}
