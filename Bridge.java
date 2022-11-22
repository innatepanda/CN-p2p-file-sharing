public class Bridge{
Bridge()
{
System.out.println("here");
}
	static {
    	try {
	      System.loadLibrary("native"); }
	    catch (UnsatisfiedLinkError e){
	    System.out.println("stack err");
	      e.printStackTrace();
	    }
	
	
    }
    public native void DownloadFile(int port, String fp, String new_fp);
 }
