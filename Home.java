import java.awt.*;   
import javax.swing.*;  
import java.awt.event.*;
import java.io.File;
import java.util.Scanner;

public class Home implements ActionListener{
    //JTextField fname,fsize; 
    JButton logout,delete,add;  
    JLabel welcome,fname,fsize;
    JPanel p;
    CardLayout crd;
    JPanel cPane;
    int flag=1;
    GridBagConstraints gbc;
    public String result="default";
    Gui g;
    Login log;
    Home(CardLayout crd, JPanel cards, Gui g)
    {
        this.g=g;
        this.crd=crd;
        this.cPane=cards;
        p = new JPanel();
        p.setLayout(new GridBagLayout());
         gbc = new GridBagConstraints();
            gbc.insets = new Insets(8, 8, 8, 8);
            gbc.gridx = 0;
            gbc.gridy = 0;
            
        p.setBounds(0,0,1000,1000);
        p.setBackground(Color.white);
       // gbc.setBackground(Color.red);  
     
        welcome=new JLabel();
        welcome.setFont (welcome.getFont ().deriveFont (20.0f));
       // gbc.gridx=1;
        gbc.anchor = GridBagConstraints.FIRST_LINE_START;
        p.add(welcome,gbc);
        
        
        logout =new JButton("Logout");
        logout.addActionListener(this);    
        gbc.gridx=6;
        p.add(logout,gbc);
        gbc.gridy++;
        gbc.gridx=0;
        add =new JButton("Add new file");//creating instance of JButton  
        //b.addActionListener(this); 
        add.addActionListener(this);
        gbc.gridy++;
        p.add(add, gbc);
        gbc.gridy++;
        
        
    }

    public JPanel getpanel()
    {
        return p;
    }
    public void changeText(String msg){
         welcome.setText("Welcome "+msg); 
    }
    public void actionPerformed(ActionEvent e) 
    {    
       
           if(e.getSource()==logout ){  
               //g.username =log.s1;
               g.Auth(g.username,"password",-1);
               //crd.show(cPane,"b");
           }
           if(e.getSource()==add ){  
          
               JFileChooser jchooser= new JFileChooser();
               jchooser.setMultiSelectionEnabled(true);
               int response =jchooser.showOpenDialog(null);
               if(response==JFileChooser.APPROVE_OPTION){
                  File[] files = jchooser.getSelectedFiles();
                  //long filesize=file.length();
                  //fname.setText(file.getName());
                  //fsize.setText("Size "+filesize);
                  for (File f: files) {
                       long filesize=f.length();
                       
                       
                       System.out.println(f.getName());
                       System.out.println("path "+f);
                       
                       
                        fname=new JLabel(f.getName());
                        fname.setFont (fname.getFont ().deriveFont (15.0f));
                        //fname.setText(f.getName());
                        gbc.gridx=0;
                        p.add(fname,gbc);
                        gbc.gridx++;

                        fsize=new JLabel("Size "+filesize);
                        fsize.setFont (fsize.getFont ().deriveFont (15.0f));
                        //fsize.setText("Size "+filesize);  
                        p.add(fsize,gbc);
                        gbc.gridx++;

                        delete=new JButton("Delete file");
                        //delete.addActionListener(this);
                        gbc.gridx++;
                        p.add(delete, gbc);
                        gbc.gridy++;
                        
                        //p.add(l4, gbc);
                  }
		  p.validate();
                  p.repaint();
		 // System.out.println("file size "+filesize+"bytes");
		 // System.out.println("file name "+file.getName());
		 // System.out.println(jchooser.getSelectedFile().length());
               }
               
               //crd.show(cPane,"b");
           }
           
         
          
            
          
       
    }
   
   
}
