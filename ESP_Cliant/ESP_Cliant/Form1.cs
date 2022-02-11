using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.Http;
using System.Net.Sockets;
using System.Text;
using System.Windows.Forms;

namespace ESP_Cliant
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void buttonOn_Click(object sender, EventArgs e)
        {
            SendCommandAsync(true);
        }


        private void buttonOff_Click(object sender, EventArgs e)
        {
            SendCommandAsync(false);
        }

        // Powershell で疎通確認
        // Test-NetConnection 172.16.80.160 -Port 80 //デフォルトはPort 80

        async System.Threading.Tasks.Task SendCommandAsync(bool OnOff)
        {
            string url = textBoxIP.Text;
            url = "http://" + url + "/?button=" +( OnOff==true?"on":"off").ToString();

using (var httpClient = new HttpClient())
{
    //   using (var request = new HttpRequestMessage(new HttpMethod("GET"), "http://172.16.80.160/?s=1"))
    using (var request = new HttpRequestMessage(new HttpMethod("GET"), url))
    {
        var response = await httpClient.SendAsync(request);
    }
}
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

    }
}
