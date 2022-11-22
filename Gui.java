import java.awt.*;   
import javax.swing.*;  
import java.awt.event.*;
public class Gui extends JFrame{
    //JTextField t1,t2,t3; 
    //JButton b;  
    JLabel l4,l1;
    JPanel  q;
    CardLayout crd;    
    JPanel cPane;  
    JButton exit; 
    Home home; 
    static String username="user";
    fileinfo finfo = new fileinfo();
    Gui(){
        cPane =new JPanel();  
        crd = new CardLayout();    
        cPane.setLayout(crd);  
       
        q = new JPanel();
   
        
        q.setLayout(new GridBagLayout());
        GridBagConstraints qgbc = new GridBagConstraints();
            qgbc.insets = new Insets(8, 8, 8, 8);
            qgbc.gridx = 0;
            qgbc.gridy = 0;
       // q.setBounds(0,0,500,500);
        //q.setBackground(Color.blue);
        
        Login login = (new Login(crd, cPane, this));
        cPane.add(login.getpanel(), "a");
      //  System.out.println("username"+g.username);
        //q.add(l4);
       
        Register reg = (new Register(crd, cPane, this));
        cPane.add(reg.getpanel(), "c");
        
        home = (new Home(crd, cPane, this));
        cPane.add(home.getpanel(), "b");
       
      
        //cPane.add(q, "b");  
       
      
       // cPane.add(q, "b");  
        setContentPane(cPane); 
             
            
    }
   
  
    static {
    	
        System.loadLibrary("native");
        
    }
    public native int Cmain();
    public native String Auth(String usr, String pwd, int choice);
    public native String File(String user, String fname[],String fpath[], int fsize[],int fno, int choice);
    public native fileinfo[] getStructArray();
    public native int getFilesNew();
    public native void DownloadFile(int port, String fp, String new_fp);
    
    
    public void changeUsername(String msg)
    {
    	 username=msg;
         home.usern=msg;
         home.changeText(msg);
    }

       public static void main(String[] args) {  
        Runtime.getRuntime().loadLibrary("aes_connector");
        
          Gui g=new Gui();          
          int res=g.Cmain();          
          if(res==0) return;
          g.setSize(700,700);  
          //g.setLayout();  
         // g. setResizable(false);
          g.setVisible(true);
          //g.setUndecorated(true);
          WindowListener exitListener = new WindowAdapter() {

            @Override
            public void windowClosing(WindowEvent e) {
                  g.Auth(username,"password",-1);
            }
           };
          g.addWindowListener(exitListener);
          //login.setDefaultCloseOperation(EXIT_ON_CLOSE); 
             
       } 
}
