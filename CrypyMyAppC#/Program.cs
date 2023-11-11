// See https://aka.ms/new-console-template for more information
using System.Runtime.InteropServices;

[DllImport("EncryptDll.dll")]
static extern void test();

try
{
    Console.WriteLine("Start");
    test();
    Console.WriteLine("End");

}
catch (Exception ex)
{
    Console.WriteLine(ex.Message);
}
finally
{
    Console.ReadKey();
}