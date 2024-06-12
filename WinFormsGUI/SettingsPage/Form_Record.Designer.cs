namespace WinFormsGUI.SettingsPage {
	partial class Form_Record {
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing) {
			if (disposing && (components != null)) {
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent() {
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form_Record));
			button1 = new Button();
			button2 = new Button();
			saveFileDialog1 = new SaveFileDialog();
			SuspendLayout();
			// 
			// button1
			// 
			button1.Location = new Point(64, 12);
			button1.Name = "button1";
			button1.Size = new Size(123, 50);
			button1.TabIndex = 0;
			button1.Text = "开始";
			button1.UseVisualStyleBackColor = true;
			button1.Click += button1_Click;
			// 
			// button2
			// 
			button2.Location = new Point(64, 68);
			button2.Name = "button2";
			button2.Size = new Size(123, 50);
			button2.TabIndex = 1;
			button2.Text = "停止";
			button2.UseVisualStyleBackColor = true;
			button2.Click += button2_Click;
			// 
			// saveFileDialog1
			// 
			saveFileDialog1.DefaultExt = "ddoa";
			saveFileDialog1.FileName = "record";
			saveFileDialog1.Filter = "DDOA录制文件|*.ddoa|所有文件|*.*";
			saveFileDialog1.InitialDirectory = "records";
			saveFileDialog1.RestoreDirectory = true;
			saveFileDialog1.FileOk += saveFileDialog1_FileOk;
			// 
			// Form_Record
			// 
			AutoScaleDimensions = new SizeF(7F, 17F);
			AutoScaleMode = AutoScaleMode.Font;
			ClientSize = new Size(254, 128);
			Controls.Add(button2);
			Controls.Add(button1);
			FormBorderStyle = FormBorderStyle.FixedSingle;
			Icon = (Icon)resources.GetObject("$this.Icon");
			MaximizeBox = false;
			MinimizeBox = false;
			Name = "Form_Record";
			ShowInTaskbar = false;
			StartPosition = FormStartPosition.CenterParent;
			Text = "录制";
			Load += Form_Record_Load;
			ResumeLayout(false);
		}

		#endregion

		private Button button1;
		private Button button2;
		private SaveFileDialog saveFileDialog1;
	}
}