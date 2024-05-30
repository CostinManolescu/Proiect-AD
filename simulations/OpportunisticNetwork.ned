package retea_oportunista.simulations;

network OpportunisticNetwork {
    parameters:
        int numNodes = default(10); // Parameter to specify the number of nodes
        int exampleValue = default(42);
        int id = default(0);

    submodules:
        node[numNodes]: MobileHost {
            @display("p=100,100");
            nodeId = id;  // Assigning unique IDs to each node based on their index
            groupId = groupNr;     // Example group ID, can be modified
            totalNodes = numNodes; 
            initialValue = exampleValue;  
        }

    connections allowunconnected:
        // Define connections if necessary
}
