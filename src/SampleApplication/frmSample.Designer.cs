namespace SampleApplication
{
    partial class frmSample
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.grpFile = new System.Windows.Forms.GroupBox();
            this.txtOutput = new System.Windows.Forms.TextBox();
            this.lblOutput = new System.Windows.Forms.Label();
            this.txtInput = new System.Windows.Forms.TextBox();
            this.lblInput = new System.Windows.Forms.Label();
            this.btnStart = new System.Windows.Forms.Button();
            this.grpImage = new System.Windows.Forms.GroupBox();
            this.pnlAfter = new System.Windows.Forms.Panel();
            this.pctAfter = new System.Windows.Forms.PictureBox();
            this.pnlBefore = new System.Windows.Forms.Panel();
            this.pctBefore = new System.Windows.Forms.PictureBox();
            this.btnSelectFile = new System.Windows.Forms.Button();
            this.btnImageStart = new System.Windows.Forms.Button();
            this.dlgOpenFile = new System.Windows.Forms.OpenFileDialog();
            this.lblBefore = new System.Windows.Forms.Label();
            this.lblAfter = new System.Windows.Forms.Label();
            this.grpFile.SuspendLayout();
            this.grpImage.SuspendLayout();
            this.pnlAfter.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pctAfter)).BeginInit();
            this.pnlBefore.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pctBefore)).BeginInit();
            this.SuspendLayout();
            // 
            // grpFile
            // 
            this.grpFile.Controls.Add(this.txtOutput);
            this.grpFile.Controls.Add(this.lblOutput);
            this.grpFile.Controls.Add(this.txtInput);
            this.grpFile.Controls.Add(this.lblInput);
            this.grpFile.Controls.Add(this.btnStart);
            this.grpFile.Location = new System.Drawing.Point(12, 12);
            this.grpFile.Name = "grpFile";
            this.grpFile.Size = new System.Drawing.Size(273, 124);
            this.grpFile.TabIndex = 5;
            this.grpFile.TabStop = false;
            this.grpFile.Text = "ファイル変換サンプル";
            // 
            // txtOutput
            // 
            this.txtOutput.Location = new System.Drawing.Point(96, 48);
            this.txtOutput.Name = "txtOutput";
            this.txtOutput.Size = new System.Drawing.Size(171, 19);
            this.txtOutput.TabIndex = 9;
            // 
            // lblOutput
            // 
            this.lblOutput.AutoSize = true;
            this.lblOutput.Location = new System.Drawing.Point(8, 51);
            this.lblOutput.Name = "lblOutput";
            this.lblOutput.Size = new System.Drawing.Size(82, 12);
            this.lblOutput.TabIndex = 8;
            this.lblOutput.Text = "出力ファイルパス";
            // 
            // txtInput
            // 
            this.txtInput.Location = new System.Drawing.Point(96, 23);
            this.txtInput.Name = "txtInput";
            this.txtInput.Size = new System.Drawing.Size(171, 19);
            this.txtInput.TabIndex = 7;
            this.txtInput.Text = "E:\\work\\1.png";
            // 
            // lblInput
            // 
            this.lblInput.AutoSize = true;
            this.lblInput.Location = new System.Drawing.Point(8, 26);
            this.lblInput.Name = "lblInput";
            this.lblInput.Size = new System.Drawing.Size(82, 12);
            this.lblInput.TabIndex = 6;
            this.lblInput.Text = "入力ファイルパス";
            // 
            // btnStart
            // 
            this.btnStart.Location = new System.Drawing.Point(96, 82);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(171, 30);
            this.btnStart.TabIndex = 5;
            this.btnStart.Text = "変換処理の開始";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.button1_Click);
            // 
            // grpImage
            // 
            this.grpImage.Controls.Add(this.lblAfter);
            this.grpImage.Controls.Add(this.lblBefore);
            this.grpImage.Controls.Add(this.pnlAfter);
            this.grpImage.Controls.Add(this.pnlBefore);
            this.grpImage.Controls.Add(this.btnSelectFile);
            this.grpImage.Controls.Add(this.btnImageStart);
            this.grpImage.Location = new System.Drawing.Point(291, 12);
            this.grpImage.Name = "grpImage";
            this.grpImage.Size = new System.Drawing.Size(510, 316);
            this.grpImage.TabIndex = 6;
            this.grpImage.TabStop = false;
            this.grpImage.Text = "イメージ変換サンプル";
            // 
            // pnlAfter
            // 
            this.pnlAfter.AutoScroll = true;
            this.pnlAfter.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pnlAfter.Controls.Add(this.pctAfter);
            this.pnlAfter.Location = new System.Drawing.Point(252, 30);
            this.pnlAfter.Name = "pnlAfter";
            this.pnlAfter.Size = new System.Drawing.Size(240, 240);
            this.pnlAfter.TabIndex = 11;
            // 
            // pctAfter
            // 
            this.pctAfter.Location = new System.Drawing.Point(0, 0);
            this.pctAfter.Name = "pctAfter";
            this.pctAfter.Size = new System.Drawing.Size(140, 140);
            this.pctAfter.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pctAfter.TabIndex = 8;
            this.pctAfter.TabStop = false;
            // 
            // pnlBefore
            // 
            this.pnlBefore.AutoScroll = true;
            this.pnlBefore.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pnlBefore.Controls.Add(this.pctBefore);
            this.pnlBefore.Location = new System.Drawing.Point(6, 30);
            this.pnlBefore.Name = "pnlBefore";
            this.pnlBefore.Size = new System.Drawing.Size(240, 240);
            this.pnlBefore.TabIndex = 10;
            // 
            // pctBefore
            // 
            this.pctBefore.Location = new System.Drawing.Point(0, 0);
            this.pctBefore.Name = "pctBefore";
            this.pctBefore.Size = new System.Drawing.Size(124, 134);
            this.pctBefore.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pctBefore.TabIndex = 1;
            this.pctBefore.TabStop = false;
            // 
            // btnSelectFile
            // 
            this.btnSelectFile.Location = new System.Drawing.Point(6, 276);
            this.btnSelectFile.Name = "btnSelectFile";
            this.btnSelectFile.Size = new System.Drawing.Size(171, 30);
            this.btnSelectFile.TabIndex = 9;
            this.btnSelectFile.Text = "画像ファイルの選択";
            this.btnSelectFile.UseVisualStyleBackColor = true;
            this.btnSelectFile.Click += new System.EventHandler(this.btnSelectFile_Click);
            // 
            // btnImageStart
            // 
            this.btnImageStart.Location = new System.Drawing.Point(252, 276);
            this.btnImageStart.Name = "btnImageStart";
            this.btnImageStart.Size = new System.Drawing.Size(171, 30);
            this.btnImageStart.TabIndex = 8;
            this.btnImageStart.Text = "変換処理の開始";
            this.btnImageStart.UseVisualStyleBackColor = true;
            this.btnImageStart.Click += new System.EventHandler(this.btnImageStart_Click);
            // 
            // lblBefore
            // 
            this.lblBefore.AutoSize = true;
            this.lblBefore.Location = new System.Drawing.Point(6, 15);
            this.lblBefore.Name = "lblBefore";
            this.lblBefore.Size = new System.Drawing.Size(85, 12);
            this.lblBefore.TabIndex = 12;
            this.lblBefore.Text = "変換前プレビュー";
            // 
            // lblAfter
            // 
            this.lblAfter.AutoSize = true;
            this.lblAfter.Location = new System.Drawing.Point(251, 15);
            this.lblAfter.Name = "lblAfter";
            this.lblAfter.Size = new System.Drawing.Size(85, 12);
            this.lblAfter.TabIndex = 13;
            this.lblAfter.Text = "変換後プレビュー";
            // 
            // frmSample
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(813, 334);
            this.Controls.Add(this.grpImage);
            this.Controls.Add(this.grpFile);
            this.Name = "frmSample";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "サンプル";
            this.grpFile.ResumeLayout(false);
            this.grpFile.PerformLayout();
            this.grpImage.ResumeLayout(false);
            this.grpImage.PerformLayout();
            this.pnlAfter.ResumeLayout(false);
            this.pnlAfter.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pctAfter)).EndInit();
            this.pnlBefore.ResumeLayout(false);
            this.pnlBefore.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pctBefore)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox grpFile;
        private System.Windows.Forms.TextBox txtOutput;
        private System.Windows.Forms.Label lblOutput;
        private System.Windows.Forms.TextBox txtInput;
        private System.Windows.Forms.Label lblInput;
        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.GroupBox grpImage;
        private System.Windows.Forms.Button btnImageStart;
        private System.Windows.Forms.Button btnSelectFile;
        private System.Windows.Forms.OpenFileDialog dlgOpenFile;
        private System.Windows.Forms.Panel pnlAfter;
        private System.Windows.Forms.PictureBox pctAfter;
        private System.Windows.Forms.Panel pnlBefore;
        private System.Windows.Forms.PictureBox pctBefore;
        private System.Windows.Forms.Label lblAfter;
        private System.Windows.Forms.Label lblBefore;

    }
}

