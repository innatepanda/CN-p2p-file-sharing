import  java.lang.Thread;
import java.awt.*;   
import javax.swing.*;  
import java.awt.event.*;
import java.io.File;
import javax.swing.AbstractAction;
import java.util.*;
import java.nio.file.Files;


public class DownloadThread extends Thread {
  
	    
    Gui g;int port; String path, fname;
    /*DownloadThread()
    {
    	//Runtime.getRuntime().loadLibrary("native");
    }*/
    
    DownloadThread(int p, String pa, String fn ){
	//g = mainpanel;
	port = p;
	path = pa;
	fname = fn;
    }
    
    public void run()
    {
        try {
            // Displaying the thread that is running
            System.out.println(
                "Thread: " + Thread.currentThread().getId());
                JFileChooser jchooser= new JFileChooser(fname);
       
	       jchooser.setSelectedFile(new File(fname));
	       int response =jchooser.showSaveDialog(null);
	       if (response == JFileChooser.APPROVE_OPTION)
	 
            	{
            		System.out.println("path:"+jchooser.getSelectedFile().toPath().toString());
                	
                	Bridge b = new Bridge();
                	b.DownloadFile(port, path, jchooser.getSelectedFile().toPath().toString());
                	
                	
                }
                
        }
        catch (Exception e) {
            // Throwing an exception
            System.out.println("Exception is caught");
        }
    }
}
