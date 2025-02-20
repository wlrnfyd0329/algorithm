import java.util.*;
import java.io.*;

public class 유혁진_1218 {
    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        for(int tc = 1; tc <= 10; tc++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int n = Integer.parseInt(st.nextToken());
            String str = br.readLine();
            Stack<Character> s = new Stack<>();
            boolean isWrong = false;
            for(int i = 0; i < n; i++) {
                char c = str.charAt(i);
                if (c == '(' || c == '[' || c == '{' || c == '<') {
                    s.push(c);
                }
                else {
                    if (s.isEmpty()) {
                        isWrong = true;
                        break;
                    }
                    else {
                        if (c == ')' && s.pop() != '(') {
                            isWrong = true;
                            break;
                        }
                        if (c == ']' && s.pop() != '[') {
                            isWrong = true;
                            break;
                        }
                        if (c == '}' && s.pop() != '{') {
                            isWrong = true;
                            break;
                        }
                        if (c == '>' && s.pop() != '<') {
                            isWrong = true;
                            break;
                        }
                    }
                }
            } 
             
            if (!s.isEmpty() || isWrong) {
                System.out.println("#" + tc + " 0");
            }
            else {
                System.out.println("#" + tc + " 1");
            }
        }
    }
}