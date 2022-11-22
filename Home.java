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
    JLabel welcome,fname,fsize,userl,fnol, noData;
    JPanel mainPanel, topPanel, dataPanel;
    CardLayout crd;
    JPanel cPane;
    GridBagConstraints main_gbc, gbc, data_gbc;
    public String result="default";
    Gui g;
    final fileinfo finfo=new fileinfo();
    String usern="user";
    Home(CardLayout crd, JPanel cards, Gui g)
    {
        this.g=g;
        this.crd=crd;
        this.cPane=cards;
        mainPanel = new JPanel();
        mainPanel.setLayout(new GridBagLayout());
         
           // gbc.setVgap(0);
        mainPanel.setBounds(0,0,700,700);
        mainPanel.setBackground(Color.black);
       // gbc.setBackground(Color.red);  
       
       main_gbc = new GridBagConstraints();
       main_gbc.insets = new Insets(2, 2, 0, 0);
       main_gbc.gridx = 0;
       main_gbc.gridy = 0;
            //gbc.weighty = 1; 
       main_gbc.weightx = 1;
       main_gbc.anchor = GridBagConstraints.PAGE_START; 
       
       noData = new JLabel(); 
       noData.setFont (noData.getFont ().deriveFont (20.0f));
       noData.setText("No Files Available");

     	topPanel = new JPanel();
	topPanel.setLayout(new GridBagLayout());
	
	topPanel.setSize( 700, 700);
	topPanel.setVisible(true);
	gbc = new GridBagConstraints();
        gbc.insets = new Insets(25, 10,10, 10);
        gbc.gridx = 0;
        gbc.gridy = 0;
            //gbc.weighty = 1; 
        gbc.weightx = 1;
        gbc.anchor = GridBagConstraints.PAGE_START; 
	
        welcome=new JLabel();
        welcome.setFont (welcome.getFont ().deriveFont (20.0f));
       // gbc.gridx=1;
        gbc.anchor = GridBagConstraints.FIRST_LINE_START;
        gbc.ipadx = 10; 
        topPanel.add(welcome,gbc);
        
        s=new JTextField(15); 
        //s.setHorizontalAlignment(JTextField.RIGHT);
        
        
        logout =new JButton("Logout");
        logout.addActionListener(this);    
        gbc.gridx=4;
        gbc.ipady = 10; 
        topPanel.add(logout,gbc);
        
        gbc.gridy=1;
        gbc.gridx=0;
        gbc.gridy++;
        
        getFiles = new JButton("Get files");     
        getFiles.addActionListener(this);
        topPanel.add(getFiles, gbc);
        gbc.ipady = 10; 
        gbc.gridx++;
        
        
        add = new JButton("Add new file");     
        add.addActionListener(this);
        topPanel.add(add, gbc);
        gbc.gridx++;
        
        search=new JButton("Search");
        search.addActionListener(this);
        //insets = new Insets(10,0,0,0) ;   
        gbc.gridx=3;
        s.setOpaque(false);
        gbc.ipady = 10;  
        topPanel.add(s, gbc);
        //search.setHorizontalAlignment(JButton.RIGHT);
        gbc.gridx=4;
        topPanel.add(search,gbc);

	
	dataPanel = new JPanel();
	dataPanel.setLayout(new GridBagLayout());
	
	dataPanel.setSize( 1000, 1000);
	dataPanel.setVisible(true);

	data_gbc = new GridBagConstraints();
	data_gbc.insets = new Insets(25, 10, 10, 10);
	data_gbc.gridx = 0;
        data_gbc.gridy = 0;
	data_gbc.weightx = 1;
	//data_gbc.weighty=2;
	data_gbc.anchor = GridBagConstraints.PAGE_START; 
        
        //gbc.weightx=1;
        //gbc.gridwidth = 5; 
        
        gbc.gridy+=2;
        
        mainPanel.add(topPanel, main_gbc);
        main_gbc.gridy+=2;
        mainPanel.add(dataPanel, main_gbc);
      
    }

    public JPanel getpanel()
    {
        return mainPanel;
    }
    
    
    public void changeText(String msg){
         welcome.setText("Welcome "+msg); 
         getFiles();
    }
    
    
    public void refreshUI(ArrayList<fileinfo> files){
            dataPanel.removeAll();
    	
            data_gbc.gridx = 0;
            data_gbc.gridy = 0;
            //gbc.weighty = 1; 
            int n = files.size();  
        
        if(n==0) 
        {
        	
        	dataPanel.add(noData, data_gbc);
        	//return;
        }
    	
    	for (int i = 0; i < n ; i++)  {

    		final fileinfo curr = files.get(i);
    		int fno = curr.fno; //number of files per user
    		if(fno==0) continue;
    		String str1 = Integer.toString(fno);
    		
	        userl=new JLabel(curr.usern);//username
	        userl.setFont(userl.getFont().deriveFont(16.0f));
	        data_gbc.anchor = GridBagConstraints.FIRST_LINE_START;	
                data_gbc.gridx=0;
                dataPanel.add(userl,data_gbc);
                
                fnol=new JLabel(str1);//no of files
                data_gbc.gridx=1;
                
                dataPanel.add(fnol,data_gbc);
                data_gbc.gridx++;
               	//data_gbc.gridy++;
                System.out.println("port numbers:"+curr.status);
	       for (int j = 0; j < fno; j++)
	       {
	       	
		       final int index = j;
		       
		       //System.out.println("path "+curr.fpath[j]);
		       
		       
			fname=new JLabel(curr.fnm[j]);
			
			data_gbc.gridx=2;
			dataPanel.add(fname,data_gbc);
			//data_gbc.gridx+=2;
                        data_gbc.gridx++;
			fsize=new JLabel("Size "+curr.fs[j]);
		      
			dataPanel.add(fsize,data_gbc);
			data_gbc.gridx++;
			
			//TODO: del only for own files, username for others
			

			
			
			
			
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
			   result = g.File(usern, nfnm,nfpath,nfs,1, 4);
			   System.out.println("--result: "+result);
			   getFiles();
			  }
			});
			delete.setText("Delete");
			gbc.gridx=4;
			gbc.ipady = 10; 
			data_gbc.gridx++;
			dataPanel.add(delete, data_gbc);
			}else
			{
				download=new JButton(new AbstractAction(""+j) {
				@Override
				  public void actionPerformed(ActionEvent e) {
				  downloadFile(curr.status, curr.fpath[index], curr.fnm[index]);
				   
				  }
				});
				download.setText("Download");
				data_gbc.gridx++;
				gbc.ipady = 10; 
				dataPanel.add(download, data_gbc);
			
			}
			
			data_gbc.gridy+=2;
			
			
			
		}
		
		
          }
           
	  dataPanel.repaint();
	  dataPanel.revalidate();
          mainPanel.repaint();
          mainPanel.revalidate();
      
    
    }
    
    public void getFiles()
    {
    	ArrayList<fileinfo> finfo   = new ArrayList<fileinfo>(Arrays.asList(g.getStructArray()));
        refreshUI(finfo);
    }
    
    
    public void downloadFile(int port, String path, String fname)
    {
    	DownloadThread d = new DownloadThread(port, path, fname);
    	d.start();
    	    	
    	    	
    /*
        File src = new File(path);
        JFileChooser jchooser= new JFileChooser(fname);
       
       jchooser.setSelectedFile(new File(fname));
       int response =jchooser.showSaveDialog(null);
       if (response == JFileChooser.APPROVE_OPTION)
 
            {
                // set the label to the path of the selected file
                //System.out.println("pathhhhh:"+jchooser.getSelectedFile().toPath());
                //File dest = jchooser.getSelectedFile();
                try{
                //Files.copy(src.toPath(), jchooser.getSelectedFile().toPath());
                     //make new file out of string downloaded
                     //copy contents to file
                     //pass new filepath 
                     
                     
                }catch(Exception e)
                {
                        System.out.println("error"+e.getMessage());
                }
            }
    */
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
                       fnm[i]=files[i].getName();
                       fpath[i]=files[i].getPath();
                  }
                       
                  result = g.File(usern, fnm,fpath,fs,files.length, 2);
                  getFiles();
                  
                  //TODO
                  
		
               }
               
               //crd.show(cPane,"b");
           }
 
       
    }
    
    
    
    
    
    
   
   
}
