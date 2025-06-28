import java.util.*;

public class Result {

    static class Package implements Comparable<Package> {
        private int index;
        private long weight;
    
        Package(int index, long weight) {
            this.index = index;
            this.weight = weight;
        }
    
        long getWeight() {
            return weight;
        }
    
        int getIndex() {
            return index;
        }
    
        @Override
        public int compareTo(Package p) {
            return Long.compare(this.weight, p.getWeight());
        }
    }
    
    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);
        int testCount = scanner.nextInt();
        ArrayList<Integer>[] results = new ArrayList[testCount];

        for (int currentTest = 0; currentTest < testCount; currentTest++) {
            int n = scanner.nextInt(); // packages count
            long w = scanner.nextLong(); // total weight

            //long[] packageWeights = new long[n];
            PriorityQueue<Package> packageWeights = new PriorityQueue<Package>(Comparator.reverseOrder());

            for (int i = 0; i < n; i++) {
                Package p = new Package(i, scanner.nextLong());
                packageWeights.add(p);
            }

            int index = 0;
            long partialWeight = 0;
            ArrayList<Integer> selectedPackages = new ArrayList<>();

            while (index < n && partialWeight <= w) {
                Package p = packageWeights.remove();
                long partialSum = partialWeight + p.getWeight();
                if (partialSum <= w) {
                    partialWeight = partialSum;
                    selectedPackages.add(p.getIndex() + 1); // +1 to print 0 as a result
                    if (partialWeight >= Math.ceil(w / 2.0)) {
                        break;
                    }
                }
                
                index++;
            }

            if (partialWeight < Math.ceil(w / 2.0)) {
                selectedPackages = new ArrayList<Integer>();
                selectedPackages.add(-1);
                results[currentTest] = selectedPackages;
            } else {
                results[currentTest] = selectedPackages;
            }
        }

        // Print the results
        for (int index = 0; index < results.length; index++) {
            ArrayList<Integer> packages = results[index];
            if (packages.getFirst() != -1) {
                System.out.println(packages.size());
            }
            for(int i = 0; i < packages.size(); i++) {
                System.out.print(packages.get(i) + " ");
            } 
            System.out.println("");
        }

        scanner.close();
    }
}
