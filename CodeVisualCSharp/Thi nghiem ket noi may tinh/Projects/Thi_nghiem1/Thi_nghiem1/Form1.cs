using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Thi_nghiem1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            Gecko.Xpcom.Initialize(Application.StartupPath + "\\xulrunner");
            geckoWeb.Navigate("http://192.168.0.102");
 
        }

        private void button1_Click(object sender, EventArgs e)
        {
            geckoWeb.Navigate(textBox1.Text);
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

       
     
    }
}
