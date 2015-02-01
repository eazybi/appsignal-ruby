require 'appsignal/integrations/capistrano/careful_logger'

module Appsignal
  class Marker
    include Appsignal::CarefulLogger

    attr_reader :marker_data, :config, :logger
    ACTION = 'markers'

    def initialize(marker_data, config, logger)
      @marker_data = marker_data
      @config = config
      @logger = logger
    end

    def transmit
      logger.info("Notifying Appsignal of deploy with: revision: #{marker_data[:revision]}, user: #{marker_data[:user]}")
      result = Appsignal::Native.transmit_marker(marker_data.to_json, 'json')
      if result == 200
        logger.info('Appsignal has been notified of this deploy!')
      else
        logger.error("#{result} when transmitting marker to #{config[:endpoint]}")
      end
    end
  end
end
