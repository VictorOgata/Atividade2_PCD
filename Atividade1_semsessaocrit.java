/*Victor de Oliveira Ogata 111838
Gaspar Afonso Rocha 112203*/
import java.util.Random;


public class Atividade1_semsessaocrit {
    public static int MAX_THREADS = 4;
    public static int N = 100000;
    static volatile long SOMA = 0; 
    static volatile long c0 = 0; 
    static volatile long c1 = 0; 
    static volatile long c2 = 0; 
    static volatile long c3 = 0; 
    static volatile long RESTO = N%MAX_THREADS; 
    static volatile int aux = 0;
    static volatile int req = 0;
    static volatile int res = 0;

    static class client extends Thread {

        private int id;
        public client(int idd){
            id = idd;
        }
        public void run() {

            for(int i = 0; i<(N/MAX_THREADS)+1;i++){
   //             while(res!=id){
                    req = id;
   //             }
               long local = SOMA;
        //       Random gen = new Random(1985);
        //        try{
        //            Thread.sleep(gen.nextInt(2147483647) % 2);
        //        }catch(InterruptedException ex){}

        if(RESTO>0 && i ==(N/MAX_THREADS)){
                SOMA = local + 1; 
                RESTO--;
                if(id == 1)c0++;
                if(id == 2)c1++;
                if(id == 3)c2++;
                if(id == 4)c3++; 
        }
        else if(i <(N/MAX_THREADS)){
            SOMA = local + 1; 
            if(id == 1)c0++;
            if(id == 2)c1++;
            if(id == 3)c2++;
            if(id == 4)c3++; 
        }
               
          //     System.out.println("Thread id = " +id +" soma = "+SOMA); 
                res = 0;

            }
            return;
        }
    }

    static class server extends Thread {
        public void run() {
            while (true) {
                while(req==0){
                    continue;}
                res = req;

                while(res!=0){
                    continue;}
                req = 0;
            }
        }
    }

    public static void main(String[] args) {
        Thread[] client = new Thread[MAX_THREADS];
        Thread server = new server();
        server.start();
        for(int i = 0;i<MAX_THREADS;i++){
            client[i] = new client(i+1);
            client[i].start();
        }
        for(int i = 0;i<MAX_THREADS;i++){
            try{
                client[i].join();
            }catch(InterruptedException ex){}
    
        } 
        System.out.println("soma = " +SOMA + " Resultado para " + MAX_THREADS +" THREADS"); 
   //     System.out.println(" Thread 1 Op = " +c0+"\n" +" Thread 2 Op = " +c1);   
        System.out.println(" Thread 1 Op = " +c0 +"\n"+" Thread 2 Op = " +c1+"\n"+" Thread 3 Op = " +c2+"\n"+" Thread 4 Op = " +c3); 
        System.exit(0);    
    }

}