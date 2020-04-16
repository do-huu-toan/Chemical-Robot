using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.IO.Ports;
namespace Thi_nghiem1
{
    public partial class Form2 : Form
    {
       
        public Form2()
        {
            InitializeComponent();
            
           
            P.Close();
         
           
        }





        private void button1_Click(object sender, EventArgs e)
        {
           // String data = "";
            if (P.IsOpen)
            {
                if (btn_set.Text == "Lock") { MessageBox.Show("Chưa Lock Hóa chất"); }
                else if (btn_set.Text == "Unlock")
                {
                if ((((txt_pt1.Text == "Fe") && (txt_pt2.Text == "H2SO4")) || ((txt_pt2.Text == "H2SO4") && (txt_pt1.Text == "Fe"))||
                    ((txt_pt1.Text == "NH4Cl") && (txt_pt2.Text == "NaOH"))||((txt_pt1.Text == "NaOH") && (txt_pt2.Text == "NH4Cl2"))||
                    ((txt_pt1.Text == "Na2CO3") && (txt_pt2.Text == "HCl"))||((txt_pt1.Text == "HCl") && (txt_pt2.Text == "Na2CO3"))))
                {
                DialogResult lkResult = MessageBox.Show("Phản ứng nguy hiểm, bản có muốn thực hiện không?", "Thông báo", MessageBoxButtons.YesNo);
                 if (lkResult == DialogResult.Yes)

                            {
                                MessageBox.Show("Ok!! Hệ thống sẽ tiếp tục tiến hành thí nghiệm");
                            }
                    if (lkResult == DialogResult.No)
                    {
                                return;
                    }
                  }
                    if (txt_pt1.Text == txt_1.Text)
                    {
                      P.Write("1"); ;;  
                    }
                    else if (txt_pt1.Text == txt_2.Text)
                    {
                        P.Write("2"); ;
                       
                   }
                    if (txt_pt2.Text == txt_1.Text)
                    {
                        P.Write("1"); ;
                       
                    }
                    else if (txt_pt2.Text == txt_2.Text)
                    {
                        P.Write("2"); ;
                        
                    }
                    P.Write("3");
                    pt(txt_1.Text, txt_2.Text);

                    
                }
           }
        }
        void pt(String a,String b)
        {
            if (((a == "BaCl2") && (b == "Na2CO3")) || ((a == "Na2CO3") && (b == "BaCl2"))) { txt_pt4.Text = "BaCO3 + NaCl"; txt_pt.Text = "Kết tủa trắng!!!"; }
            if (((a == "BaCl2") && (b == "H2SO4")) || ((a == "H2SO4") && (b == "BaCl2"))) {txt_pt4.Text = "BaSO4 + 2HCl";txt_pt.Text = "Kết tủa trắng!!!";}
            if (((a == "AgNO3") && (b == "HCl")) || ((a == "HCl") && (b == "AgNO3"))) { txt_pt4.Text = "AgCl + HNO3"; txt_pt.Text = "Kết tủa trắng!!!"; }
            if (((a == "CuCl2") && (b == "NaOH")) || ((a == "NaOH") && (b == "CuCl2"))) {txt_pt4.Text = "Cu(OH)2 + NaCl";txt_pt.Text = "Dung dịch kết tủa màu xanh lam!!!";}
            if (((a == "FeCl2") && (b == "NaOH")) || ((a == "NaOH") && (b == "FeCl2"))) {txt_pt4.Text = "Fe(OH)2 + NaCl";txt_pt.Text = "Kết tủa trắng xanh!!!";}
            if (((a == "FeCl3") && (b == "NaOH")) || ((a == "NaOH") && (b == "FeCl3"))) { txt_pt4.Text = "Fe(OH)3 + NaCl"; txt_pt.Text = "Kết tủa nâu đỏ!!!"; }
            if (((a == "AlCl3") && (b == "NaOH")) || ((a == "NaOH") && (b == "AlCl3"))) { txt_pt4.Text = "Al(OH)3 + NaCl"; txt_pt.Text = "Kết tủa trắng bông keo!!!"; }
            if (((a == "Fe") && (b == "H2SO4")) || ((a == "H2SO4") && (b == "Fe"))) { txt_pt4.Text = "Fe2(SO4)3 + SO2+ H2O"; txt_pt.Text = "Tạo khí mùi hắc"; }
            if (((a == "NH4Cl") && (b == "NaOH")) || ((a == "NaOH") && (b == "NH4Cl"))) { txt_pt4.Text = "NaCl + NH3 + H2O"; txt_pt.Text = "Khí mùi khai!!!"; }
            if (((a == "Na2CO3") && (b == "HCl")) || ((a == "HCl") && (b == "Na2CO3"))) { txt_pt4.Text = "NaCl + CO2 + H2O"; txt_pt.Text = "Tạo Khí CO2!!!"; }
            if (((a == "CaCO3") && (b == "HCl")) || ((a == "HCl") && (b == "CaCO3"))) { txt_pt4.Text = "CaCl2 + CO2 + H2O"; txt_pt.Text = "Tạo Khí CO2!!!"; }
        }
            
        

        private void button2_Click(object sender, EventArgs e)
        {
            


            if (P.IsOpen)
            {
         
                P.Write("5");
            }
            else { MessageBox.Show(" Chưa kết nối cổng COM!!!!"); }

        }

       

        private void btn_Connect_Click(object sender, EventArgs e)
        {
            if (!P.IsOpen)
            {
                if (cb_CongCOM.Text == "") { MessageBox.Show("Chưa chọn cổng COM"); }
                else
                {
                    P.PortName = cb_CongCOM.Text;
                    P.Open();
                }
            }
            else { P.Close(); }
           
        }


        private void timer2_Tick(object sender, EventArgs e)
        {
            
            if (P.IsOpen) { lb_TrangThai.Text = "Đã kết nối";
            lb_TrangThai.ForeColor = Color.Green;
                btn_Connect.Text = "Ngắt kết nối"; 
            }
            else { 
                lb_TrangThai.Text = "Chưa kết nối";
                lb_TrangThai.ForeColor = Color.Red;
                btn_Connect.Text = "Kết nối";
            }
            
        }

        private void button3_Click(object sender, EventArgs e)
        {
           
            if (P.IsOpen) { P.Write("5"); }
            P.Close();
            Close();
           
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            cb_CongCOM.DataSource = SerialPort.GetPortNames();//Quét các cổng Serial đang hoạt động lên ComboBox1
        }

        private void btn_set_Click(object sender, EventArgs e)
        {

            if (btn_set.Text == "Lock")
            {
                btn_set.Text = "Unlock";
                txt_1.Enabled = false;
                txt_2.Enabled = false;
                txt_3.Enabled = false;
            }
            else if (btn_set.Text == "Unlock")
            {
                btn_set.Text = "Lock";
                txt_1.Enabled = true;
                txt_2.Enabled = true;
                txt_3.Enabled = true;
            }
        }

        private void txt_mom_Click(object sender, EventArgs e)
        {
            if (P.IsOpen)
            {
                if (txt_mom.Text == "Kẹp ống") { txt_mom.Text = "Nhả ống"; P.Write("7"); }
                else if (txt_mom.Text == "Nhả ống") { txt_mom.Text = "Kẹp ống"; P.Write("8"); }
            }
        }

        private void btn_stream_Click(object sender, EventArgs e)
        {
            //System.Diagnostics.Process.Start(Application.StartupPath + "\\CamStudio 2.7\\Recorder.exe");
            Form1 live = new Form1();
            live.ShowDialog();
            

        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (P.IsOpen)
            {
                P.Write("X");
                double t = Convert.ToDouble(textBox1.Text);
                double l = t / 0.003;
                int n = Convert.ToInt32(l);
                String s = n.ToString();
                P.Write(s);
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (P.IsOpen)
            {
                P.Write("Z");
                double t = Convert.ToDouble(textBox2.Text);
                double l = t/0.00175;
                int n = Convert.ToInt32(l);
                String s = n.ToString();
                P.Write(s);
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            if (P.IsOpen)
            {
                if (button6.Text == "Hút khí")
                {
                    button6.Text = "Tắt hút khí";
                    P.Write("Y");
                }
                else if (button6.Text == "Tắt hút khí")
                {
                    button6.Text = "Hút khí";
                    P.Write("T");
                }
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            if (P.IsOpen)
            {
                if (button7.Text == "Lên") { button7.Text = "Xuống"; P.Write("L"); }
                else if (button7.Text == "Xuống") { button7.Text = "Lên"; P.Write("X"); }
            }
        }

   
       

        

    }
}
