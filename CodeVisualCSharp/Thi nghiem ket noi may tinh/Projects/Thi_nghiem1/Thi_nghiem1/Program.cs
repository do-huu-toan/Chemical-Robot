using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace Thi_nghiem1
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form2());//Khởi tạo cho chạy form1 đầu tiên rồi người dùng sẽ sử dụng từ form1
        }
    }
}
