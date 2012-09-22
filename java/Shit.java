public class Shit
{
    public static void main(String[] args){
        B a = new B(); 
            a.hey();
            //System.out.println("instance of B");
    }
}
class A
{
       protected String z = "aaa";
       public void hey(){
        System.out.println("hey im A");    
       } 
}
class B extends A 
{
       public void hey(){
        System.out.println("hey im B: "+z);    
       } 
        
}
