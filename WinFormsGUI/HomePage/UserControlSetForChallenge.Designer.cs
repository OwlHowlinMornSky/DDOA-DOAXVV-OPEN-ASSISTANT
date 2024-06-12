namespace WinFormsGUI {
	partial class UserControlSetForChallenge {
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
			gpBox_AwardMatch = new GroupBox();
			radioBtn_AwardIgnore = new RadioButton();
			radioBtn_AwardPlay = new RadioButton();
			radioBtn_AwardNo = new RadioButton();
			gpBox_TargetMatch = new GroupBox();
			radioButton_recordMatch = new RadioButton();
			radioBtn_NewMatch = new RadioButton();
			radioBtn_PreviousMatch = new RadioButton();
			checkBox_useCamFP = new CheckBox();
			checkBox_PauseForMannual = new CheckBox();
			checkBox_autoUseDrink = new CheckBox();
			gpBox_AwardMatch.SuspendLayout();
			gpBox_TargetMatch.SuspendLayout();
			SuspendLayout();
			// 
			// gpBox_AwardMatch
			// 
			gpBox_AwardMatch.Controls.Add(radioBtn_AwardIgnore);
			gpBox_AwardMatch.Controls.Add(radioBtn_AwardPlay);
			gpBox_AwardMatch.Controls.Add(radioBtn_AwardNo);
			gpBox_AwardMatch.Location = new Point(3, 111);
			gpBox_AwardMatch.Name = "gpBox_AwardMatch";
			gpBox_AwardMatch.Size = new Size(200, 107);
			gpBox_AwardMatch.TabIndex = 5;
			gpBox_AwardMatch.TabStop = false;
			gpBox_AwardMatch.Text = "奖励挑战赛";
			// 
			// radioBtn_AwardIgnore
			// 
			radioBtn_AwardIgnore.AutoSize = true;
			radioBtn_AwardIgnore.ImeMode = ImeMode.NoControl;
			radioBtn_AwardIgnore.Location = new Point(6, 76);
			radioBtn_AwardIgnore.Name = "radioBtn_AwardIgnore";
			radioBtn_AwardIgnore.Size = new Size(86, 21);
			radioBtn_AwardIgnore.TabIndex = 2;
			radioBtn_AwardIgnore.Text = "忽略并继续";
			radioBtn_AwardIgnore.UseVisualStyleBackColor = true;
			radioBtn_AwardIgnore.CheckedChanged += AwardMatch_RadioBtn_CheckedChanged;
			// 
			// radioBtn_AwardPlay
			// 
			radioBtn_AwardPlay.AutoSize = true;
			radioBtn_AwardPlay.ImeMode = ImeMode.NoControl;
			radioBtn_AwardPlay.Location = new Point(6, 49);
			radioBtn_AwardPlay.Name = "radioBtn_AwardPlay";
			radioBtn_AwardPlay.Size = new Size(74, 21);
			radioBtn_AwardPlay.TabIndex = 1;
			radioBtn_AwardPlay.Text = "尝试进入";
			radioBtn_AwardPlay.UseVisualStyleBackColor = true;
			radioBtn_AwardPlay.CheckedChanged += AwardMatch_RadioBtn_CheckedChanged;
			// 
			// radioBtn_AwardNo
			// 
			radioBtn_AwardNo.AutoSize = true;
			radioBtn_AwardNo.Checked = true;
			radioBtn_AwardNo.ImeMode = ImeMode.NoControl;
			radioBtn_AwardNo.Location = new Point(6, 22);
			radioBtn_AwardNo.Name = "radioBtn_AwardNo";
			radioBtn_AwardNo.Size = new Size(62, 21);
			radioBtn_AwardNo.TabIndex = 0;
			radioBtn_AwardNo.TabStop = true;
			radioBtn_AwardNo.Text = "不检测";
			radioBtn_AwardNo.UseVisualStyleBackColor = true;
			radioBtn_AwardNo.CheckedChanged += AwardMatch_RadioBtn_CheckedChanged;
			// 
			// gpBox_TargetMatch
			// 
			gpBox_TargetMatch.Controls.Add(radioButton_recordMatch);
			gpBox_TargetMatch.Controls.Add(radioBtn_NewMatch);
			gpBox_TargetMatch.Controls.Add(radioBtn_PreviousMatch);
			gpBox_TargetMatch.Location = new Point(3, 3);
			gpBox_TargetMatch.Name = "gpBox_TargetMatch";
			gpBox_TargetMatch.Size = new Size(200, 102);
			gpBox_TargetMatch.TabIndex = 4;
			gpBox_TargetMatch.TabStop = false;
			gpBox_TargetMatch.Text = "游戏选项";
			// 
			// radioButton_recordMatch
			// 
			radioButton_recordMatch.AutoSize = true;
			radioButton_recordMatch.Location = new Point(6, 75);
			radioButton_recordMatch.Name = "radioButton_recordMatch";
			radioButton_recordMatch.Size = new Size(110, 21);
			radioButton_recordMatch.TabIndex = 2;
			radioButton_recordMatch.TabStop = true;
			radioButton_recordMatch.Text = "录制指定的比赛";
			radioButton_recordMatch.UseVisualStyleBackColor = true;
			radioButton_recordMatch.CheckedChanged += MatchSet_RadioBtn_CheckedChanged;
			// 
			// radioBtn_NewMatch
			// 
			radioBtn_NewMatch.AutoSize = true;
			radioBtn_NewMatch.ImeMode = ImeMode.NoControl;
			radioBtn_NewMatch.Location = new Point(6, 49);
			radioBtn_NewMatch.Name = "radioBtn_NewMatch";
			radioBtn_NewMatch.Size = new Size(62, 21);
			radioBtn_NewMatch.TabIndex = 1;
			radioBtn_NewMatch.Text = "新比赛";
			radioBtn_NewMatch.UseVisualStyleBackColor = true;
			radioBtn_NewMatch.CheckedChanged += MatchSet_RadioBtn_CheckedChanged;
			// 
			// radioBtn_PreviousMatch
			// 
			radioBtn_PreviousMatch.AutoSize = true;
			radioBtn_PreviousMatch.Checked = true;
			radioBtn_PreviousMatch.ImeMode = ImeMode.NoControl;
			radioBtn_PreviousMatch.Location = new Point(6, 22);
			radioBtn_PreviousMatch.Name = "radioBtn_PreviousMatch";
			radioBtn_PreviousMatch.Size = new Size(79, 21);
			radioBtn_PreviousMatch.TabIndex = 0;
			radioBtn_PreviousMatch.TabStop = true;
			radioBtn_PreviousMatch.Text = "当前/上次";
			radioBtn_PreviousMatch.UseVisualStyleBackColor = true;
			radioBtn_PreviousMatch.CheckedChanged += MatchSet_RadioBtn_CheckedChanged;
			// 
			// checkBox_useCamFP
			// 
			checkBox_useCamFP.AutoSize = true;
			checkBox_useCamFP.Location = new Point(9, 224);
			checkBox_useCamFP.Name = "checkBox_useCamFP";
			checkBox_useCamFP.Size = new Size(172, 21);
			checkBox_useCamFP.TabIndex = 6;
			checkBox_useCamFP.Text = "自动使用拍摄恢复FP的机会";
			checkBox_useCamFP.UseVisualStyleBackColor = true;
			checkBox_useCamFP.CheckedChanged += CheckBox_useCamFP_CheckedChanged;
			// 
			// checkBox_PauseForMannual
			// 
			checkBox_PauseForMannual.AutoSize = true;
			checkBox_PauseForMannual.Location = new Point(9, 278);
			checkBox_PauseForMannual.Name = "checkBox_PauseForMannual";
			checkBox_PauseForMannual.Size = new Size(195, 21);
			checkBox_PauseForMannual.TabIndex = 7;
			checkBox_PauseForMannual.Text = "开始任务时暂停并请求手动导航";
			checkBox_PauseForMannual.UseVisualStyleBackColor = true;
			checkBox_PauseForMannual.CheckedChanged += CheckBox_PauseForMannual_CheckedChanged;
			// 
			// checkBox_autoUseDrink
			// 
			checkBox_autoUseDrink.AutoSize = true;
			checkBox_autoUseDrink.Location = new Point(9, 251);
			checkBox_autoUseDrink.Name = "checkBox_autoUseDrink";
			checkBox_autoUseDrink.Size = new Size(136, 21);
			checkBox_autoUseDrink.TabIndex = 8;
			checkBox_autoUseDrink.Text = "自动使用FP恢复饮料";
			checkBox_autoUseDrink.UseVisualStyleBackColor = true;
			checkBox_autoUseDrink.CheckedChanged += CheckBox_autoUseDrink_CheckedChanged;
			// 
			// UserControlSetForChallenge
			// 
			AutoScaleDimensions = new SizeF(7F, 17F);
			AutoScaleMode = AutoScaleMode.Font;
			Controls.Add(checkBox_autoUseDrink);
			Controls.Add(checkBox_PauseForMannual);
			Controls.Add(checkBox_useCamFP);
			Controls.Add(gpBox_AwardMatch);
			Controls.Add(gpBox_TargetMatch);
			Name = "UserControlSetForChallenge";
			Size = new Size(210, 334);
			Load += UserControlSetForLegacyCha_Load;
			gpBox_AwardMatch.ResumeLayout(false);
			gpBox_AwardMatch.PerformLayout();
			gpBox_TargetMatch.ResumeLayout(false);
			gpBox_TargetMatch.PerformLayout();
			ResumeLayout(false);
			PerformLayout();
		}

		#endregion

		private GroupBox gpBox_AwardMatch;
		private RadioButton radioBtn_AwardIgnore;
		private RadioButton radioBtn_AwardPlay;
		private RadioButton radioBtn_AwardNo;
		private GroupBox gpBox_TargetMatch;
		private RadioButton radioBtn_NewMatch;
		private RadioButton radioBtn_PreviousMatch;
		private CheckBox checkBox_useCamFP;
		private CheckBox checkBox_PauseForMannual;
		private CheckBox checkBox_autoUseDrink;
		private RadioButton radioButton_recordMatch;
	}
}
