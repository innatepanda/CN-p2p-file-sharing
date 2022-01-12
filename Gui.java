import java.awt.*;   
import javax.swing.*;  
import java.awt.event.*;
public class Gui extends JFrame implements ActionListener{
    //JTextField t1,t2,t3; 
    //JButton b;  
    JLabel l4;
    JPanel  q;
    CardLayout crd;    
    JPanel cPane;  
    JButton exit;  
    String username="User"; 
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
        l4=new JLabel("text");
        Register reg = (new Register(crd, cPane, this));
        cPane.add(reg.getpanel(), "c");
       // l4.setText(reg.result);
        q.add(l4);

        exit =new JButton("Exit");
        exit.addActionListener(this);
        qgbc.gridy++;
        q.add(exit,qgbc);
        cPane.add(q, "b");  
       
        setContentPane(cPane); 
             
            
    }
    public void changeText(String msg)
    {
        l4.setText(msg);
    }
    public void actionPerformed(ActionEvent e) 
    {    
        if(e.getSource()==exit){  
            
            this.Auth(username,"password",-1);
            //System.out.println("close result: "+resC);
            //System.exit(0);
        }
    }
    public void SetUserName(String usern){
        username=usern;
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
          g.setDefaultCloseOperation(EXIT_ON_CLOSE);    
       } 
}
