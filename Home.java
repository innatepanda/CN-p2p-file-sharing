import java.awt.*;   
import javax.swing.*;  
import java.awt.event.*;
import java.io.File;

import java.util.Scanner;

public class Home implements ActionListener{
    JTextField s; 
    JButton logout,delete,add,search;  
    JLabel welcome,fname,fsize;
    JPanel p;
    CardLayout crd;
    JPanel cPane;
    GridBagConstraints gbc;
    public String result="default";
    Gui g;
    Home(CardLayout crd, JPanel cards, Gui g)
    {
        this.g=g;
        this.crd=crd;
        this.cPane=cards;
        p = new JPanel();
        p.setLayout(new GridBagLayout());
         gbc = new GridBagConstraints();
            gbc.insets = new Insets(2, 2, 0, 0);
            gbc.gridx = 0;
            gbc.gridy = 0;
            //gbc.weighty = 1; 
            gbc.weightx = 1;
            gbc.anchor = GridBagConstraints.PAGE_START; 
           // gbc.setVgap(0);
        p.setBounds(0,0,700,700);
        p.setBackground(Color.white);
       // gbc.setBackground(Color.red);  
     
        welcome=new JLabel();
        welcome.setFont (welcome.getFont ().deriveFont (20.0f));
       // gbc.gridx=1;
        gbc.anchor = GridBagConstraints.FIRST_LINE_START;
        p.add(welcome,gbc);
        
        s=new JTextField(15); 
        //s.setHorizontalAlignment(JTextField.RIGHT);
        
        search=new JButton("Search");
        search.addActionListener(this);    
        gbc.gridx=1;
        s.setOpaque(false);
        gbc.ipady = 10;  
        p.add(s, gbc);
        //search.setHorizontalAlignment(JButton.RIGHT);
        gbc.gridx=2;
        p.add(search,gbc);
        
        logout =new JButton("Logout");
        logout.addActionListener(this);    
        gbc.gridx=3;
        p.add(logout,gbc);
        
        gbc.gridy=1;
        gbc.gridx=0;
        add =new JButton("Add new file");     
        add.addActionListener(this);
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
               g.Auth(g.username,"password", -1);
               //crd.show(cPane,"b");
           }
           if(e.getSource()==add ){  
          
               JFileChooser jchooser= new JFileChooser();
               //FileListAccessory accessory = new FileListAccessory(jchooser);
               //jchooser.setAccessory(accessory);
               jchooser.setMultiSelectionEnabled(true);
               int response =jchooser.showSaveDialog(null);
               if(response==JFileChooser.APPROVE_OPTION){
                  File[] files = jchooser.getSelectedFiles();
                  
                  for (int i = 0; i < files.length; i++)  {
                       long filesize=files[i].length();
                       
                       
                       System.out.println(files[i].getName());
                       System.out.println("path "+files[i]);
                       
                       
                        fname=new JLabel(files[i].getName());
                        
                        gbc.gridx=0;
                        p.add(fname,gbc);
                        gbc.gridx++;

                        fsize=new JLabel("Size "+filesize);
                      
                        p.add(fsize,gbc);
                        gbc.gridx++;

                        delete=new JButton("Delete file");
                        //delete.addActionListener(this);
                        gbc.gridx++;
                        p.add(delete, gbc);
                        gbc.gridy++;
                        result=g.Files(g.username,files[i].getName(),(int)filesize,files.length, 1);
                        //System.out.println(files.length);
                        
                        //p.add(l4, gbc);
                  }
            
		  p.validate();
                  p.repaint();
		
               }
               
               //crd.show(cPane,"b");
           }
 
       
    }
   
   
}
