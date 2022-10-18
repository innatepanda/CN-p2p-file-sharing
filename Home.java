import java.awt.*;   
import javax.swing.*;  
import java.awt.event.*;
import java.io.File;
import javax.swing.AbstractAction;
import java.util.*;
import java.nio.file.Files;

class fileinfo{
   String usern;
   int status;
   int fs[];
   int fno;
   String fnm[];
   String fpath[];
   fileinfo(){}
   
}

public class Home implements ActionListener{
    JTextField s; 
    JButton logout,download, delete ,add,search, getFiles;  
    JLabel welcome,fname,fsize,userl,fnol;
    JPanel p, dataPanel;
    CardLayout crd;
    JPanel cPane;
    GridBagConstraints gbc, data_gbc;
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
        
        
        getFiles = new JButton("Get files");     
        getFiles.addActionListener(this);
        p.add(getFiles, gbc);
        gbc.gridx++;
        
        
        add = new JButton("Add new file");     
        add.addActionListener(this);
        p.add(add, gbc);
        gbc.gridx=0;
        
		dataPanel = new JPanel();
		dataPanel.setLayout(new GridBagLayout());
		
		dataPanel.setSize( 1700, 700);
		dataPanel.setVisible(true);
        
		data_gbc = new GridBagConstraints();
		data_gbc.insets = new Insets(2, 2, 2, 2);
		data_gbc.weightx = 1;
		data_gbc.weighty=2;
		//data_gbc.anchor = GridBagConstraints.PAGE_START; 
        
        gbc.weightx=1;
        gbc.gridwidth = 5; 
        
        gbc.gridy+=2;
        
        p.add(dataPanel, gbc);
        
        
        
        
        
    }

    public JPanel getpanel()
    {
        return p;
    }
    public void changeText(String msg){
         welcome.setText("Welcome "+msg); 
    }
    
    
    public void refreshUI(ArrayList<fileinfo> files){
    	dataPanel.removeAll();
    	
            data_gbc.gridx = 0;
            data_gbc.gridy = 0;
            //gbc.weighty = 1; 
            
    	//System.out.println(files);
    	for (int i = 0; i < files.size(); i++)  {

    		final fileinfo curr = files.get(i);
    		int fno = curr.fno; //number of files per user
    		String str1 = Integer.toString(fno);
    		//System.out.println(fno);
    		
	       //long filesize=files.elementAt(i).length();
	       userl=new JLabel(curr.usern);//username
			
                data_gbc.gridx=0;
                dataPanel.add(userl,data_gbc);
                
                fnol=new JLabel(str1);//no of files
                data_gbc.gridx++;
                
                dataPanel.add(fnol,data_gbc);
                data_gbc.gridx++;
               	data_gbc.gridy++;
                
	       for (int j = 0; j < fno; j++)
	       {
	       	
		       final int index = j;
		       
		       //System.out.println("path "+curr.fpath[j]);
		       
		       
			fname=new JLabel(curr.fnm[j]);
			
			data_gbc.gridx=0;
			dataPanel.add(fname,gbc);
			data_gbc.gridx+=2;

			fsize=new JLabel("Size "+curr.fs[j]);
		      
			dataPanel.add(fsize,data_gbc);
			data_gbc.gridx++;
			
			//TODO: del only for own files, username for others
			

			download=new JButton(new AbstractAction(""+j) {
			@Override
			  public void actionPerformed(ActionEvent e) {
			  downloadFile(curr.fpath[index], curr.fnm[index]);
			   System.out.println("--result: "+(usern.equals(curr.usern)));
			  }
			});
			download.setText("Download");
			data_gbc.gridx++;
			dataPanel.add(download, data_gbc);
			
			if(usern.equals( curr.usern)){
			
			delete=new JButton(new AbstractAction(""+j) {
			@Override
			  public void actionPerformed(ActionEvent e) {
			  
			  int nfs[]=new int[1]; String nfnm[]=new String[1]; String nfpath[]=new String[1];
			   nfs[0]=(int)curr.fs[index];
			   nfnm[0]=curr.fnm[index];
			   nfpath[0]=curr.fpath[index];
			    //System.out.println("--del path: "+files[index]);
			    //TODO
			   result = g.Files(usern, nfnm,nfpath,nfs,1, 4);
			   System.out.println("--result: "+result);
			  }
			});
			delete.setText("Delete");
			data_gbc.gridx++;
			dataPanel.add(delete, data_gbc);
			}
			
			data_gbc.gridy+=2;
			
			
			
		}
		
		//System.out.println(files.length);
		
		//p.add(l4, gbc);
		
		
          }
          
                  
            
	  
          p.repaint();
          p.revalidate();
      
    
    }
    
    public void downloadFile(String path, String fname)
    {
        File src = new File(path);
        JFileChooser jchooser= new JFileChooser(fname);
       
       jchooser.setSelectedFile(new File(fname));
       int response =jchooser.showSaveDialog(null);
       if (response == JFileChooser.APPROVE_OPTION)
 
            {
                // set the label to the path of the selected file
                System.out.println("pathhhhh:"+jchooser.getSelectedFile().toPath());
                //File dest = jchooser.getSelectedFile();
                try{
                Files.copy(src.toPath(), jchooser.getSelectedFile().toPath());
                }catch(Exception e)
                {
                        System.out.println("error"+e.getMessage());
                }
            }
    
    }
    
    public void getFiles()
    {
    	ArrayList<fileinfo> finfo   = new ArrayList<fileinfo>(Arrays.asList(g.getStructArray()));
                
                
               
        for (int i = 0; i < finfo.size(); i++) {
             System.out.println("---Test " + i + "---");
             System.out.println("Username:" + finfo.get(i).usern);
             //System.out.println("Status:" + finfo.elementAt(i).status);
             System.out.println("File name:" + finfo.get(i).fnm[0]);
             System.out.println("File no.:" + finfo.get(i).fno);
      }
      
      refreshUI(finfo);
    }
    public void actionPerformed(ActionEvent e) 
    {    
       
           if(e.getSource()==logout ){  
               //g.username =log.s1;
               g.Auth(g.username,"password", -1);
               //crd.show(cPane,"b");
           }
           if(e.getSource()==getFiles ){  
               //fileinfo[] finfo = new fileinfo[20];
               //Vector<fileinfo> finfo = new Vector<fileinfo>();
               getFiles();
                  
           }
           if(e.getSource()==add ){  
          
               JFileChooser jchooser= new JFileChooser();
               //FileListAccessory accessory = new FileListAccessory(jchooser);
               //jchooser.setAccessory(accessory);
               jchooser.setMultiSelectionEnabled(true);
               int response =jchooser.showSaveDialog(null);
               
               if(response==JFileChooser.APPROVE_OPTION){
                  File[] files = jchooser.getSelectedFiles();
                  
        
                  final int fs[] = new int[50]; final String fnm[] = new String[50]; final String fpath[] = new String[100];
                  System.out.println("--n files:"+files.length);
                  
                  for (int i = 0; i < files.length; i++)  {
                  
                       fs[i]=(int)files[i].length();
                       System.out.println("--length:"+ fs[i]);
                       fnm[i]=files[i].getName();
                       fpath[i]=files[i].getPath();
                  }
                       
                  result = g.Files(usern, fnm,fpath,fs,files.length, 2);
                  
                  //TODO
                  
		
               }
               
               //crd.show(cPane,"b");
           }
 
       
    }
    
    
    
    
    
    
   
   
}
