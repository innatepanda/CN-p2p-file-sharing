import java.awt.*;   
import javax.swing.*;  
import java.awt.event.*;
public class Gui extends JFrame{
    //JTextField t1,t2,t3; 
    //JButton b;  
    JLabel l4;
    JPanel  q;
    CardLayout crd;    
    JPanel cPane;  
    JButton exit;  
    static String username="user"; 
    Gui(){
        cPane =new JPanel();  
        crd = new CardLayout();    
        cPane.setLayout(crd);  
       
        q = new JPanel();
   
        q = new JPanel();
        q.setLayout(new GridBagLayout());
        GridBagConstraints qgbc = new GridBagConstraints();
            qgbc.insets = new Insets(8, 8, 8, 8);
            qgbc.gridx = 0;
            qgbc.gridy = 0;
        q.setBounds(0,0,500,500);
        //q.setBackground(Color.blue);
        
        Login login = (new Login(crd, cPane, this));
        cPane.add(login.getpanel(), "a");
        //q.add(l4);
       
        Register reg = (new Register(crd, cPane, this));
        cPane.add(reg.getpanel(), "c");
    
        Home home = (new Home(crd, cPane, this));
        cPane.add(home.getpanel(), "b");

      
        //cPane.add(q, "b");  
       
      
       // cPane.add(q, "b");  
        setContentPane(cPane); 
             
            
    }
   
  
   
    static {
        System.loadLibrary("native");
    }
    public native int Cmain();
    public native String Auth(String usr, String pwd, int status);
    

       public static void main(String[] args) {  
          Gui g=new Gui();
          int res=g.Cmain();
          g.setSize(500,500);  
          //g.setLayout();  
          g.setVisible(true);
         
          System.out.println("java");
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
