import java.awt.*;   
import javax.swing.*;  
import java.awt.event.*;
import java.io.File;
import javax.swing.AbstractAction;
import java.util.Scanner;

class fileinfo{
   String usern;
   int status;
   int fs[];
   int fno;
   String fnm[];
   String fpath[];
   
}
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
    final fileinfo finfo=new fileinfo();
    String usern="user";
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
                  
                  fileinfo[] finfo=g.getStructArray();
                  for (int i = 0; i < finfo.length; i++) {
            System.out.println("Username:" + finfo[i].usern);
            System.out.println("Status:" + finfo[i].status);
            System.out.println("File no.:" + finfo[i].fno);
        }
                  
                  
                  
                  
               
                  
                  final int fs[] = new int[50]; final String fnm[] = new String[50]; final String fpath[] = new String[100];
                  System.out.println("--n files:"+files.length);
                  
                  for (int i = 0; i < files.length; i++)  {
                  
                       fs[i]=(int)files[i].length();
                       System.out.println("--length:"+ fs[i]);
                       fnm[i]=files[i].getName();
                       fpath[i]=files[i].getPath();
                  }
                       
                  result = g.Files(usern, fnm,fpath,fs,files.length, 2);
                  
                  
                  for (int i = 0; i < files.length; i++)  {
                       long filesize=files[i].length();
                       
                       final int index = i;
                       System.out.println(files[i].getName());
                       System.out.println("path "+files[i]);
                       
                       
                        fname=new JLabel(files[i].getName());
                        
                        gbc.gridx=0;
                        p.add(fname,gbc);
                        gbc.gridx++;

                        fsize=new JLabel("Size "+filesize);
                      
                        p.add(fsize,gbc);
                        gbc.gridx++;

                        delete=new JButton(new AbstractAction(""+i) {
                        @Override
			  public void actionPerformed(ActionEvent e) {
			  
			  int nfs[]=new int[1]; String nfnm[]=new String[1]; String nfpath[]=new String[1];
			    nfs[0]=(int)files[index].length();
                           nfnm[0]=files[index].getName();
                           nfpath[0]=files[index].getPath();
			    System.out.println("--del path: "+files[index]);
			    result = g.Files(usern, nfnm,nfpath,nfs,1, 4);
			    System.out.println("--result: "+result);
			  }
			});
			delete.setText("Delete");
                        gbc.gridx++;
                        p.add(delete, gbc);
                        gbc.gridy++;
                        
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
