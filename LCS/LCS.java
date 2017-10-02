
public class LCS {
	
	 char[][] getLongestCommonSubsequence(String a, String b){
		int m = a.length();
		int n = b.length();
		int[][] c = new int[m+1][n+1];
		
		char[][] d = new char[m+1][n+1];
		
		for(int i=0; i<=m; i++){
			for(int j=0; j<=n; j++){
				if(i==0 || j==0){
					c[i][j]=0;
					d[i][j]='0';
				}else if(a.charAt(i-1)==b.charAt(j-1)){
					c[i][j] = 1 + c[i-1][j-1];
					d[i][j] = '\\';
				}else{
					if(c[i-1][j]>=c[i][j-1]){
						c[i][j] = c[i-1][j];
						 d[i][j] = '|';
					}else{
						c[i][j] = c[i][j] = c[i][j-1];
						d[i][j] = '-';
					}
				}
			}
		}
		
		for(int i = 0; i<=m; i++){
			for(int j = 0;j<=n; j++)
			System.out.print(c[i][j]);
			System.out.print("\n");
		}System.out.print("\n");
		
		return d;
	}
	
	 void Printlcs(char[][] tab, String x, int i, int j){
		 LCS nowy = new LCS();
		 if(i == 0 || j == 0)
			 return;
		 if(tab[i][j]=='\\'){
			 nowy.Printlcs(tab, x, i-1, j-1);
			 i--;
			 System.out.print(x.charAt(i));
		 }else if(tab[i][j]=='|'){
			 nowy.Printlcs(tab, x, i-1, j);
		 }else
			 nowy.Printlcs(tab, x, i, j-1);
	 }
	 
	public static void main(String[] args){
		//odpalamy java LCS string1 string2
		//javac LCS.java
		if(args.length==2){
			LCS najdluzszy = new LCS();
			String a = args[0];//"alibaba";
			String b = args[1];//"kalimalba";
			int m = a.length();
			int n = b.length();
			char[][] l= new char[m+1][n+1];
			l = najdluzszy.getLongestCommonSubsequence(a, b);
			for(int i = 0; i<=m; i++){
				for(int j = 0;j<=n; j++)
					System.out.print(l[i][j]);
				System.out.print("\n");
			}
			System.out.print("\n");
			najdluzszy.Printlcs(l, a, m, n);
		}
	}
}
