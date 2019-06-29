using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Collections;

namespace SampleApplication
{
    public partial class frmSample : Form
    {
        public frmSample()
        {
            InitializeComponent();
        }

        /// <summary>
        /// ボタン押下時処理
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button1_Click(object sender, EventArgs e)
        {
            ArrayList arrayParam = new ArrayList();
            arrayParam.Add(txtInput.Text);
            arrayParam.Add(txtOutput.Text);

            System.Threading.Thread objThred = new System.Threading.Thread(new System.Threading.ParameterizedThreadStart(StartConvert));
            objThred.Start(arrayParam);
        }

        /// <summary>
        /// 変換処理（ファイル指定）
        /// </summary>
        private void StartConvert(object param)
        {
            string strInput = ((ArrayList)param)[0].ToString();
            string strOutput = ((ArrayList)param)[1].ToString();

            Waifu2xSDK objWaifu2x = new Waifu2xSDK();
            bool bolResult = objWaifu2x.Convert(strInput, strOutput, 4, 2.0, E_Noise_Level.level1, E_Process.gpu);
            objWaifu2x.Dispose();

            if (bolResult == true)
            {
                MessageBox.Show("完了");
            }
            else
            {
                MessageBox.Show(objWaifu2x.GetErrorMessage());
            }   
        }

        /// <summary>
        /// 画像ファイルの選択
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnSelectFile_Click(object sender, EventArgs e)
        {
            if (dlgOpenFile.ShowDialog(this) == System.Windows.Forms.DialogResult.OK)
            {
                pctBefore.Image = System.Drawing.Image.FromFile(dlgOpenFile.FileName);
            }
        }

        /// <summary>
        /// 変換処理（ビットマップ指定）
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnImageStart_Click(object sender, EventArgs e)
        {
            Bitmap bmpWork = null;

            Bitmap bmpSrc = new Bitmap(pctBefore.Image.Width, pctBefore.Image.Height, System.Drawing.Imaging.PixelFormat.Format24bppRgb);
            Graphics grdSrc = Graphics.FromImage(bmpSrc);
            grdSrc.DrawImage(pctBefore.Image, new Point(0, 0));

            Waifu2xSDK objWaifu2x = new Waifu2xSDK();
            bool bolResult = objWaifu2x.Convert(bmpSrc, ref bmpWork, 4, 2.0, E_Noise_Level.level1, E_Process.gpu);
            objWaifu2x.Dispose();

            if (bolResult == true)
            {
                pctAfter.Image = bmpWork;
                pctAfter.Image.Save("E:\\work\\" + DateTime.Now.ToString("yyyyMMdd_HHmmss") + ".bmp");
                MessageBox.Show("完了");
            }
            else
            {
                MessageBox.Show(objWaifu2x.GetErrorMessage());
            }   
        }


    }
}
