public class JavaService{
        public static void main( String[] args){ 
                for( int i = 1; i > 0; ++i ){
                        System.out.println("I don't know java");
                        try{
                                Thread.sleep(1000);
                        } catch( Exception e ){
                                System.out.println("dungooft");
                        }
                }
        }
}
